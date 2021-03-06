// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"

#include <darefl/model/experimentaldata_types.h>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/experimentaldatamodel.h>

#include <QSignalSpy>
#include <mvvm/model/modelutils.h>
#include <mvvm/standarditems/graphitem.h>

using namespace ModelView;

//! Tests of ExperimentalDataModel.

class ExperimentalDataModelTest : public ::testing::Test
{
public:
    ~ExperimentalDataModelTest();
    RealDataStruct getRealDataStruct() const;
};

ExperimentalDataModelTest::~ExperimentalDataModelTest() = default;

RealDataStruct ExperimentalDataModelTest::getRealDataStruct() const
{
    RealDataStruct output;
    output.type = "Intensity";
    output.name = "path";

    output.axis = std::vector<double>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    output.axis_name = "axis_name";
    output.axis_unit = "a.u.";

    output.data = std::vector<double>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    output.data_name = "data_name";
    output.data_unit = "a.u.";

    return output;
}

//! Test the initial state of the model
TEST_F(ExperimentalDataModelTest, initialState)
{
    ExperimentalDataModel model;

    EXPECT_EQ(2, model.rootItem()->childrenCount());
}

//! Test the addDataToCollection method
TEST_F(ExperimentalDataModelTest, addDataToCollection)
{
    ExperimentalDataModel model;
    int default_child_count = CanvasItem().childrenCount();
    auto root_view_item = Utils::TopItem<CanvasContainerItem>(&model);
    auto root_container_item = Utils::TopItem<ExperimentalDataContainerItem>(&model);

    auto data_group_item = model.addDataToCollection(getRealDataStruct(), root_view_item);
    EXPECT_EQ(default_child_count + 1, data_group_item->childrenCount());
    EXPECT_EQ(1, root_container_item->childrenCount());

    model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item);
    EXPECT_EQ(default_child_count + 2, data_group_item->childrenCount());
    EXPECT_EQ(2, root_container_item->childrenCount());

    model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item);
    EXPECT_EQ(default_child_count + 3, data_group_item->childrenCount());
    EXPECT_EQ(3, root_container_item->childrenCount());
}

//! Test the removeAllDataFromCollection method
TEST_F(ExperimentalDataModelTest, removeAllDataFromCollection)
{
    ExperimentalDataModel model;
    auto root_view_item = Utils::TopItem<CanvasContainerItem>(&model);
    auto root_container_item = Utils::TopItem<ExperimentalDataContainerItem>(&model);

    auto data_group_item = model.addDataToCollection(getRealDataStruct(), root_view_item);
    model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item);
    model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item);

    model.removeAllDataFromCollection(root_view_item);

    EXPECT_EQ(0, root_view_item->childrenCount());
    EXPECT_EQ(0, root_container_item->childrenCount());
}

//! test the removeDataFromCollection method
TEST_F(ExperimentalDataModelTest, removeDataFromCollection)
{
    ExperimentalDataModel model;
    int default_child_count = CanvasItem().childrenCount();
    auto root_view_item = Utils::TopItem<CanvasContainerItem>(&model);
    auto root_container_item = Utils::TopItem<ExperimentalDataContainerItem>(&model);

    CanvasItem* data_group_item_1 = nullptr;
    for (int i = 0; i < 10; ++i) {
        data_group_item_1 =
            model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item_1);
    }

    CanvasItem* data_group_item_2 = nullptr;
    for (int i = 0; i < 10; ++i) {
        data_group_item_2 =
            model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item_2);
    }

    EXPECT_EQ(2, root_view_item->childrenCount());
    EXPECT_EQ(20, root_container_item->childrenCount());
    EXPECT_EQ(10 + default_child_count, data_group_item_1->childrenCount());
    EXPECT_EQ(10 + default_child_count, data_group_item_2->childrenCount());

    std::vector<SessionItem*> items_to_delete;
    auto children = data_group_item_1->children();
    for (int i = default_child_count + 2; i < 5 + default_child_count; ++i) {
        items_to_delete.push_back(children[i]);
    }

    model.removeDataFromCollection(items_to_delete);
    EXPECT_EQ(2, root_view_item->childrenCount());
    EXPECT_EQ(17, root_container_item->childrenCount());
    EXPECT_EQ(7 + default_child_count, data_group_item_1->childrenCount());
    EXPECT_EQ(10 + default_child_count, data_group_item_2->childrenCount());

    model.removeDataFromCollection({data_group_item_2});
    EXPECT_EQ(1, root_view_item->childrenCount());
    EXPECT_EQ(7, root_container_item->childrenCount());
    EXPECT_EQ(7 + default_child_count, data_group_item_1->childrenCount());
}

//! Test the canvasesNameIdentifier method.

TEST_F(ExperimentalDataModelTest, availableCanvasesInfo)
{
    ExperimentalDataModel model;
    auto root_view_item = Utils::TopItem<CanvasContainerItem>(&model);

    for (int i = 0; i < 10; ++i) {
        model.addDataToCollection(getRealDataStruct(), root_view_item, nullptr);
    }

    auto data_group_names = model.availableCanvasesInfo();

    EXPECT_EQ(10, data_group_names.size());
    for (auto pair : data_group_names) {
        auto item = model.findItem(pair.second);
        EXPECT_EQ(pair.first, item->displayName());
    }
}

//! test the checkAllGroup method
TEST_F(ExperimentalDataModelTest, checkAllGroup)
{
    ExperimentalDataModel model;

    std::vector<SessionItem*> items(10, new CanvasItem);
    EXPECT_EQ(true, model.checkAllGroup(items));

    items.push_back(new SessionItem);
    EXPECT_EQ(false, model.checkAllGroup(items));
}

//! test the checkAllGraph method
TEST_F(ExperimentalDataModelTest, checkAllGraph)
{
    ExperimentalDataModel model;
    auto root_view_item = Utils::TopItem<CanvasContainerItem>(&model);

    CanvasItem* data_group_item_1 = nullptr;
    for (int i = 0; i < 10; ++i) {
        data_group_item_1 =
            model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item_1);
    }
    auto data_children = data_group_item_1->children();
    std::vector<SessionItem*> graph_items;
    std::copy_if(data_children.begin(), data_children.end(), std::back_inserter(graph_items),
                 [](auto item) { return dynamic_cast<GraphItem*>(item); });
    EXPECT_EQ(data_group_item_1, model.checkAllGraph(graph_items));

    CanvasItem* data_group_item_2 = nullptr;
    for (int i = 0; i < 10; ++i) {
        data_group_item_2 =
            model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item_2);
    }
    data_children = data_group_item_2->children();
    std::copy_if(data_children.begin(), data_children.end(), std::back_inserter(graph_items),
                 [](auto item) { return dynamic_cast<GraphItem*>(item); });
    EXPECT_EQ(nullptr, model.checkAllGraph(graph_items));
}

//! Test the itemIsEditable method
TEST_F(ExperimentalDataModelTest, itemEditable)
{
    ExperimentalDataModel model;

    EXPECT_EQ(true, model.itemEditable(new GraphItem));
    EXPECT_EQ(true, model.itemEditable(new CanvasItem));
    EXPECT_EQ(true, model.itemEditable(new CanvasContainerItem));
    EXPECT_EQ(false, model.itemEditable(new SessionItem));
}

//! Test the dragEnabled method
TEST_F(ExperimentalDataModelTest, dragEnabled)
{
    ExperimentalDataModel model;

    EXPECT_EQ(true, model.dragEnabled(new GraphItem));
    EXPECT_EQ(true, model.dragEnabled(new CanvasItem));
    EXPECT_EQ(false, model.dragEnabled(new CanvasContainerItem));
    EXPECT_EQ(false, model.dragEnabled(new SessionItem));
}

//! Test the dropEnabled method
TEST_F(ExperimentalDataModelTest, dropEnabled)
{
    ExperimentalDataModel model;

    EXPECT_EQ(false, model.dropEnabled(new GraphItem));
    EXPECT_EQ(true, model.dropEnabled(new CanvasItem));
    EXPECT_EQ(false, model.dropEnabled(new CanvasContainerItem));
    EXPECT_EQ(false, model.dropEnabled(new SessionItem));
}

//! test the dragDropItem method with two groups
TEST_F(ExperimentalDataModelTest, dragDropItemGroup)
{
    ExperimentalDataModel model;
    int default_child_count = CanvasItem().childrenCount();
    auto root_view_item = Utils::TopItem<CanvasContainerItem>(&model);
    auto root_container_item = Utils::TopItem<ExperimentalDataContainerItem>(&model);

    CanvasItem* data_group_item_1 = nullptr;
    for (int i = 0; i < 10; ++i) {
        data_group_item_1 =
            model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item_1);
    }

    CanvasItem* data_group_item_2 = nullptr;
    for (int i = 0; i < 10; ++i) {
        data_group_item_2 =
            model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item_2);
    }

    EXPECT_EQ(2, root_view_item->childrenCount());
    EXPECT_EQ(20, root_container_item->childrenCount());
    EXPECT_EQ(10 + default_child_count, data_group_item_1->childrenCount());
    EXPECT_EQ(10 + default_child_count, data_group_item_2->childrenCount());

    EXPECT_EQ(true, model.dragDropItem(data_group_item_2, data_group_item_1));
    EXPECT_EQ(1, root_view_item->childrenCount());
    EXPECT_EQ(20, root_container_item->childrenCount());
    EXPECT_EQ(20 + default_child_count, data_group_item_1->childrenCount());
}

//! test the dragDropItem method with graph item
TEST_F(ExperimentalDataModelTest, dragDropItemGraph)
{
    ExperimentalDataModel model;
    int default_child_count = CanvasItem().childrenCount();
    auto root_view_item = Utils::TopItem<CanvasContainerItem>(&model);
    auto root_container_item = Utils::TopItem<ExperimentalDataContainerItem>(&model);

    CanvasItem* data_group_item_1 = nullptr;
    for (int i = 0; i < 10; ++i) {
        data_group_item_1 =
            model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item_1);
    }

    CanvasItem* data_group_item_2 = nullptr;
    for (int i = 0; i < 10; ++i) {
        data_group_item_2 =
            model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item_2);
    }
    auto data_children = data_group_item_2->children();
    std::vector<SessionItem*> graph_items;
    std::copy_if(data_children.begin(), data_children.end(), std::back_inserter(graph_items),
                 [](auto item) { return dynamic_cast<GraphItem*>(item); });

    EXPECT_EQ(2, root_view_item->childrenCount());
    EXPECT_EQ(20, root_container_item->childrenCount());
    EXPECT_EQ(10 + default_child_count, data_group_item_1->childrenCount());
    EXPECT_EQ(10 + default_child_count, data_group_item_2->childrenCount());

    EXPECT_EQ(true, model.dragDropItem(graph_items[0], data_group_item_1));
    EXPECT_EQ(true, model.dragDropItem(graph_items[1], data_group_item_1));
    EXPECT_EQ(true, model.dragDropItem(graph_items[2], data_group_item_1));

    EXPECT_EQ(2, root_view_item->childrenCount());
    EXPECT_EQ(20, root_container_item->childrenCount());
    EXPECT_EQ(13 + default_child_count, data_group_item_1->childrenCount());
    EXPECT_EQ(7 + default_child_count, data_group_item_2->childrenCount());
}

//! test the mergeItems method
TEST_F(ExperimentalDataModelTest, mergeItems)
{
    ExperimentalDataModel model;
    int default_child_count = CanvasItem().childrenCount();
    auto root_view_item = Utils::TopItem<CanvasContainerItem>(&model);
    auto root_container_item = Utils::TopItem<ExperimentalDataContainerItem>(&model);

    CanvasItem* data_group_item_1 = nullptr;
    for (int i = 0; i < 10; ++i) {
        data_group_item_1 =
            model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item_1);
    }

    CanvasItem* data_group_item_2 = nullptr;
    for (int i = 0; i < 10; ++i) {
        data_group_item_2 =
            model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item_2);
    }

    CanvasItem* data_group_item_3 = nullptr;
    for (int i = 0; i < 10; ++i) {
        data_group_item_3 =
            model.addDataToCollection(getRealDataStruct(), root_view_item, data_group_item_3);
    }

    EXPECT_EQ(3, root_view_item->childrenCount());
    EXPECT_EQ(30, root_container_item->childrenCount());
    EXPECT_EQ(10 + default_child_count, data_group_item_1->childrenCount());
    EXPECT_EQ(10 + default_child_count, data_group_item_2->childrenCount());
    EXPECT_EQ(10 + default_child_count, data_group_item_3->childrenCount());

    EXPECT_EQ(true, model.mergeItems({data_group_item_1, data_group_item_2, data_group_item_3}));

    EXPECT_EQ(1, root_view_item->childrenCount());
    EXPECT_EQ(30, root_container_item->childrenCount());
    EXPECT_EQ(30 + default_child_count, data_group_item_1->childrenCount());
}
