import dearpygui.dearpygui as dpg

dpg.create_context()


# callback runs when user attempts to connect attributes
def link_callback(sender, app_data):
    # app_data -> (link_id1, link_id2)
    node_from = dpg.get_item_configuration(app_data[0])
    node_to = dpg.get_item_configuration(app_data[1])

    if node_to['label'] != 'ID':
        print('Can link only to ID')
        return

    dpg.configure_item(dpg.get_item_children(app_data[0])[1][0], enabled=False)
    dpg.set_item_source(dpg.get_item_children(app_data[0])[1][0], dpg.get_item_children(app_data[1])[1][0])
    dpg.add_node_link(app_data[0], app_data[1], parent=sender)

# callback runs when user attempts to disconnect attributes
def delink_callback(sender, app_data):
    # app_data -> link_id
    dpg.delete_item(app_data)

def add_node():
    node = dpg.add_node(label="Node", parent="Editor", pos=(200, 200))
    node_id = dpg.add_node_attribute(label="ID", parent=node)
    node_next_id = dpg.add_node_attribute(label="Next ID", parent=node, attribute_type=dpg.mvNode_Attr_Output)
    node_text = dpg.add_node_attribute(label="Text", parent=node, attribute_type=dpg.mvNode_Attr_Static)

    dpg.add_input_text(label="ID", width=200, parent=node_id)
    dpg.add_input_text(label="Next ID", width=200, parent=node_next_id)
    dpg.add_input_text(label="Text", multiline=True, width=200, height=150, parent=node_text)


def print_me(sender):
    print(f"Menu Item: {sender}")


with dpg.window(tag="Primary Window", width=400, height=400):
    with dpg.node_editor(tag="Editor", callback=link_callback, delink_callback=delink_callback):
        pass


with dpg.font_registry():
    with dpg.font("Roboto-Regular.ttf", size=16, default_font=True):
        dpg.add_font_range_hint(dpg.mvFontRangeHint_Cyrillic)

dpg.show_documentation()
dpg.show_font_manager()
dpg.show_item_registry()
dpg.setup_registries()
dpg.create_viewport(title='Editor', width=800, height=600)
with dpg.viewport_menu_bar():
    dpg.add_menu_item(label="New", callback=add_node)
dpg.setup_dearpygui()
dpg.show_viewport()
dpg.set_primary_window("Primary Window", True)
dpg.start_dearpygui()
dpg.destroy_context()