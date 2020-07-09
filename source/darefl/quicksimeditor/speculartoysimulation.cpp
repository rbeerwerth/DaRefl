// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/quicksimeditor/fouriertransform.h>
#include <darefl/quicksimeditor/materialprofile.h>
#include <darefl/quicksimeditor/speculartoysimulation.h>
#include <mvvm/utils/containerutils.h>
#include <stdexcept>
#include <thread>

namespace
{
const int delay_mksec = 500;
const int simulation_steps_count = 500;
} // namespace

using namespace ModelView;

SpecularToySimulation::SpecularToySimulation(const multislice_t& multislice)
    : input_data(multislice)
{
}

void SpecularToySimulation::runSimulation()
{
    /* wish for actual procedure
    // auto std::vector<BA::Slices> processedSlices(input_data);

    progress_handler.reset();
    for (int i = 0; i < simulation_steps_count; ++i) {

        if (progress_handler.has_interrupt_request())
            throw std::runtime_error("Interrupt request");

        auto q = …;
        k = 0.5 * q;

        auto result = strategy.Execute(processedSlices, kvector_t(0, 0, k)).front();
        specular_result[i] = SpecularIntensity(result.front());
        progress_handler.setCompletedTicks(1);
    }
    */

    // actual simulation
    auto [xmin, xmax] = MaterialProfile::DefaultMaterialProfileLimits(input_data);
    auto profile =
        MaterialProfile::CalculateProfile(input_data, simulation_steps_count, xmin, xmax);
    auto specular = fourier_transform(profile);
    specular_result.xmin = 0.0;
    specular_result.xmax = specular.size();
    specular_result.data = ModelView::Utils::Real(specular);

    // Mimicking long simulation time, reporting progress and canceling, if necessary.
    progress_handler.reset();
    for (int i = 0; i < simulation_steps_count; ++i) {
        if (progress_handler.has_interrupt_request())
            throw std::runtime_error("Interrupt request");

        progress_handler.setCompletedTicks(1);
        std::this_thread::sleep_for(std::chrono::microseconds(delay_mksec));
    }
}

void SpecularToySimulation::setProgressCallback(ModelView::ProgressHandler::callback_t callback)
{
    progress_handler.setMaxTicksCount(simulation_steps_count);
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
