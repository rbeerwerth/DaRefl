// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayerRoughness.cpp
//! @brief     Implements class LayerRoughness.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include <darefl/minikernel/MultiLayer/LayerRoughness.h>
#include <darefl/minikernel/Basics/BornAgainNamespace.h>
#include <darefl/minikernel/Basics/MathConstants.h>
//#include <darefl/minikernel/Parametrization/RealParameter.h>

LayerRoughness::LayerRoughness() : m_sigma(0), m_hurstParameter(0), m_lateralCorrLength(0)
{
    initialize();
}

//! Constructor of layer roughness.
//! @param sigma: rms of the roughness in nanometers
//! @param hurstParameter: hurst parameter which describes how jagged the interface,
//! dimensionless [0.0, 1.0], where 0.0 gives more spikes, 1.0 more smoothness
//! @param lateralCorrLength: lateral correlation length of the roughness in nanometers
LayerRoughness::LayerRoughness(double sigma, double hurstParameter, double lateralCorrLength)
    : m_sigma(sigma), m_hurstParameter(hurstParameter), m_lateralCorrLength(lateralCorrLength)
{
    initialize();
}

void LayerRoughness::initialize()
{
    setName(BornAgain::LayerBasicRoughnessType);
//    registerParameter(BornAgain::Sigma, &m_sigma);
//    registerParameter(BornAgain::Hurst, &m_hurstParameter);
//    registerParameter(BornAgain::CorrelationLength, &m_lateralCorrLength)
//        .setUnit(BornAgain::UnitsNm)
//        .setNonnegative();
}

/* ************************************************************************* */
//! Power spectral density of the surface roughness is a result of two-dimensional
//! Fourier transform of the correlation function of the roughness profile.
//!
//! Based on the article
//! D.K.G. de Boer, Physical review B, Volume 51, Number 8, 15 February 1995
//! "X-ray reflection and transmission by rough surfaces"
/* ************************************************************************* */
double LayerRoughness::getSpectralFun(const kvector_t kvec) const
{
    double H = m_hurstParameter;
    double clength2 = m_lateralCorrLength * m_lateralCorrLength;
    double Qpar2 = kvec.x() * kvec.x() + kvec.y() * kvec.y();
    return 4.0 * M_PI * H * m_sigma * m_sigma * clength2
           * std::pow((1.0 + Qpar2 * clength2), (-1 - H));
}

//! Correlation function of the roughness profile

double LayerRoughness::getCorrFun(const kvector_t k) const
{
    double H = m_hurstParameter;
    double clength = m_lateralCorrLength;
    double R = sqrt(k.x() * k.x() + k.y() * k.y());
    return m_sigma * m_sigma * std::exp(-1.0 * std::pow(R / clength, 2. * H));
}
