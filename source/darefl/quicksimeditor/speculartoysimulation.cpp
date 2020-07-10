// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <algorithm>
#include <darefl/minikernel/Computation/Slice.h>
#include <darefl/minikernel/Material/MaterialFactoryFuncs.h>
#include <darefl/minikernel/MultiLayer/LayerRoughness.h>
#include <darefl/quicksimeditor/fouriertransform.h>
#include <darefl/quicksimeditor/materialprofile.h>
#include <darefl/quicksimeditor/speculartoysimulation.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/utils/containerutils.h>
#include <stdexcept>
#include <thread>

namespace
{
// const int delay_mksec = 500;
const int simulation_points = 500;
std::vector<BornAgain::Slice> createBornAgainSlices(const multislice_t& multislice);
} // namespace

using namespace ModelView;

SpecularToySimulation::SpecularToySimulation(const multislice_t& multislice)
    : input_data(multislice), strategy(std::make_unique<SpecularScalarTanhStrategy>())
{
}

void SpecularToySimulation::runSimulation()
{
    auto slices = createBornAgainSlices(input_data);
    auto qvalues = ModelView::FixedBinAxisItem::create(simulation_points, specular_result.xmin,
                                                       specular_result.xmax)
                       ->binCenters();

    specular_result.data.reserve(simulation_points);

    progress_handler.reset();
    for (auto q : qvalues) {
        if (progress_handler.has_interrupt_request())
            throw std::runtime_error("Interrupt request");

        auto kz = 0.5 * q;
        auto coeff = std::move(strategy->Execute(slices, kvector_t(0, 0, -kz)).front());
        specular_result.data.emplace_back(std::norm(coeff->getScalarR()));

        progress_handler.setCompletedTicks(1);
    }

    // temporarily log it by hand
    std::for_each(specular_result.data.begin(), specular_result.data.end(),
                  [](auto& value) { value = std::log(value); });
}

void SpecularToySimulation::setProgressCallback(ModelView::ProgressHandler::callback_t callback)
{
    progress_handler.setMaxTicksCount(simulation_points);
    progress_handler.subscribe(callback);
}

SpecularToySimulation::Result SpecularToySimulation::simulationResult() const
{
    return specular_result;
}

SpecularToySimulation::Result SpecularToySimulation::sld_profile(const multislice_t& multislice,
                                                                 int n_points)
{
    auto [xmin, xmax] = MaterialProfile::DefaultMaterialProfileLimits(multislice);
    auto profile = MaterialProfile::CalculateProfile(multislice, n_points, xmin, xmax);
    return {xmin, xmax, ModelView::Utils::Real(profile)};
}

namespace
{
std::vector<BornAgain::Slice> createBornAgainSlices(const multislice_t& multislice)
{
    std::vector<BornAgain::Slice> result;
    result.reserve(multislice.size());

    for (auto& slice : multislice) {
        auto material = MaterialBySLD("", slice.material.real(), slice.material.imag());
        auto roughness = LayerRoughness(slice.sigma, 0., 0.);

        result.emplace_back(slice.thickness, material, roughness);
    }

    return result;
}
} // namespace
