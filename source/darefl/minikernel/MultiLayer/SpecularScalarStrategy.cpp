// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularScalarStrategy.cpp
//! @brief     Implements class SpecularScalarStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include <darefl/minikernel/MultiLayer/SpecularScalarStrategy.h>
#include <darefl/minikernel/Computation/Slice.h>
#include <darefl/minikernel/MultiLayer/KzComputation.h>
#include <darefl/minikernel/MultiLayer/LayerRoughness.h>
#include <Eigen/Dense>
#include <stdexcept>

namespace
{
const LayerRoughness* GetBottomRoughness(const std::vector<BornAgain::Slice>& slices,
                                         const size_t slice_index);
} // namespace

ISpecularStrategy::coeffs_t SpecularScalarStrategy::Execute(const std::vector<BornAgain::Slice>& slices,
                                                            const kvector_t& k) const
{
    std::vector<complex_t> kz = KzComputation::computeReducedKz(slices, k);
    return Execute(slices, kz);
}

ISpecularStrategy::coeffs_t SpecularScalarStrategy::Execute(const std::vector<BornAgain::Slice>& slices,
                                                            const std::vector<complex_t>& kz) const
{
    if (slices.size() != kz.size())
        throw std::runtime_error("Number of slices does not match the size of the kz-vector");

    ISpecularStrategy::coeffs_t result;
    for (auto& coeff : computeTR(slices, kz))
        result.push_back(std::make_unique<ScalarRTCoefficients>(coeff));

    return result;
}

std::vector<ScalarRTCoefficients>
SpecularScalarStrategy::computeTR(const std::vector<BornAgain::Slice>& slices,
                                  const std::vector<complex_t>& kz) const
{
    const size_t N = slices.size();
    std::vector<ScalarRTCoefficients> coeff(N);

    for (size_t i = 0; i < N; ++i)
        coeff[i].kz = kz[i];

    if (N == 1) { // If only one layer present, there's nothing left to calculate
        coeff[0].t_r = {1.0, 0.0};
        return coeff;
    } else if (kz[0] == 0.0) { // If kz in layer 0 is zero, R0 = -T0 and all others equal to 0
        coeff[0].t_r = {1.0, -1.0};
        for (size_t i = 1; i < N; ++i)
            coeff[i].t_r.setZero();
        return coeff;
    }

    // Calculate transmission/refraction coefficients t_r for each layer, from bottom to top.
    size_t start_index = N - 2;
    calculateUpFromLayer(coeff, slices, kz, start_index);
    return coeff;
}

void SpecularScalarStrategy::setZeroBelow(std::vector<ScalarRTCoefficients>& coeff,
                                          size_t current_layer)
{
    size_t N = coeff.size();
    for (size_t i = current_layer + 1; i < N; ++i) {
        coeff[i].t_r.setZero();
    }
}

bool SpecularScalarStrategy::calculateUpFromLayer(std::vector<ScalarRTCoefficients>& coeff,
                                                  const std::vector<BornAgain::Slice>& slices,
                                                  const std::vector<complex_t>& kz,
                                                  size_t slice_index) const
{
    coeff[slice_index + 1].t_r(0) = 1.0;
    coeff[slice_index + 1].t_r(1) = 0.0;
    std::vector<complex_t> factors(slice_index + 2);
    factors[slice_index + 1] = complex_t(1, 0);
    for (size_t j = 0; j <= slice_index; ++j) {
        size_t i = slice_index - j; // start from bottom
        double sigma = 0.0;
        if (const auto roughness = GetBottomRoughness(slices, i))
            sigma = roughness->getSigma();

        coeff[i].t_r = transition(kz[i], kz[i + 1], sigma, slices[i].thickness(), coeff[i + 1].t_r);

        if (std::isinf(std::norm(coeff[i].t_r(0))) || std::isnan(std::norm(coeff[i].t_r(0)))) {
            coeff[i].t_r(0) = 1.0;
            coeff[i].t_r(1) = 0.0;

            setZeroBelow(coeff, i);
        }

        // normalize the t-coefficient in each step of the computation
        // this avoids an overflow in the backwards propagation
        // the used factors are stored in order to correct the amplitudes
        // in forward direction at the end of the computation
        factors[i] = coeff[i].t_r(0);
        coeff[i].t_r = coeff[i].t_r / coeff[i].t_r(0);
    }

    // now correct all amplitudes by dividing the with the remaining factors in forward direction
    // at some point this divison underflows, which is the point when all further amplitudes are set
    // to zero
    auto dumpingFactor = complex_t(1, 0);
    for (size_t j = 1; j <= slice_index + 1; ++j) {
        dumpingFactor = dumpingFactor * factors[j - 1];
        if (std::isinf(std::norm(dumpingFactor))) {
            setZeroBelow(coeff, j - 1);
            break;
        }
        coeff[j].t_r = coeff[j].t_r / dumpingFactor;
    }

    // this return value is meaningless now, this procedure should always succeed
    return true;
}

namespace
{
const LayerRoughness* GetBottomRoughness(const std::vector<BornAgain::Slice>& slices, const size_t slice_index)
{
    if (slice_index + 1 < slices.size())
        return slices[slice_index + 1].topRoughness();
    return nullptr;
}
} // namespace
