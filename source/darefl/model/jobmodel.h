// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MODEL_JOBMODEL_H
#define DAREFL_MODEL_JOBMODEL_H

#include <mvvm/model/sessionmodel.h>

namespace ModelView
{
class Data1DItem;
class GraphViewportItem;
class ItemPool;
} // namespace ModelView

class JobItem;
class CanvasItem;
class SpecularInstrumentItem;

//! Contains results of quick reflectometry simulations.
class JobModel : public ModelView::SessionModel
{
public:
    JobModel();
    JobModel(std::shared_ptr<ModelView::ItemPool> pool);

    ModelView::Data1DItem* sld_data() const;
    ModelView::GraphViewportItem* sld_viewport() const;

    ModelView::Data1DItem* specular_data() const;
    CanvasItem* specular_viewport() const;

    void updateReferenceGraphFrom(const SpecularInstrumentItem* instrument);

private:
    JobItem* job_item() const;
    void init_model();
};

#endif // DAREFL_MODEL_JOBMODEL_H
