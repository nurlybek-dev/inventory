import json, uuid
import dearpygui.dearpygui as dpg

dpg.create_context()

TYPES=['START', 'STORY', 'CHOICE', 'COMBAT', 'ABILITY CHECK', 'END']

def save():
    childs = dpg.get_item_children('Editor')
    links = childs[0]
    nodes = childs[1]
    link_ids = {}
    data_links = []
    data = {'links': [], 'dialogues': []}
    for child in nodes:
        node = dpg.get_item_info(child)
        node_pos = dpg.get_item_pos(child)
        node_data = {'pos': node_pos, 'choices': []}
        node_attributes = node['children'][1]
        for attribute in node_attributes:
            attr_info = dpg.get_item_info(attribute)
            if attr_info['type'] == 'mvAppItemType::mvButton':
                continue
            dpg_input = attr_info['children'][1][0]
            label = dpg.get_item_label(dpg_input)
            if label == 'ID':
                node_data['id'] = dpg.get_value(dpg_input)
                node_data['uuid'] = uuid.uuid4().hex
                link_ids[attribute] = node_data['uuid']
            elif label == 'Next ID':
                user_data = dpg.get_item_user_data(attribute)
                if user_data and 'link_id' in user_data:
                    link_id = uuid.uuid4().hex
                    link_ids[attribute] = link_id
                    node_data['link_id'] = link_id
                    data_links.append([attribute, dpg.get_item_user_data(attribute)['link_id']])
                    link_id = dpg.get_item_user_data(attribute)['link_id']
                    value = dpg.get_item_children(link_id)[1][0]
                    node_data['nextID'] = dpg.get_value(value)
                else:
                    node_data['nextID'] = dpg.get_value(dpg_input)
            elif label == 'Type':
                node_data['type'] = dpg.get_value(dpg_input)
            elif label == 'Text':
                node_data['text'] = dpg.get_value(dpg_input)
            elif label == 'Choice':
                user_data = dpg.get_item_user_data(attribute)
                if user_data and 'link_id' in user_data:
                    choice_id = uuid.uuid4().hex
                    link_ids[attribute] = choice_id
                    link_id = dpg.get_item_user_data(attribute)['link_id']
                    value = dpg.get_item_children(link_id)[1][0]
                    data_links.append([attribute, link_id])

                node_data['choices'].append({
                    'id': choice_id,
                    'text': dpg.get_value(dpg_input),
                    'nextID': dpg.get_value(value)
                })

        data['dialogues'].append(node_data)

    for link in data_links:
        data['links'].append([link_ids[link[0]], link_ids[link[1]]])

    with open('data.json', 'w') as f:
        f.write(json.dumps(data))



def load():
    with open('data.json', 'r') as f:
        data = json.loads(f.read())

    link_ids = {}
    for node in data['dialogues']:
        node_id = node['id']
        node_id, node_next_id, choice_ids = add_node(
            None, None, node['pos'], node['id'], node['nextID'], node['type'], node['text'], node['choices']
        )
        if 'uuid' in node:
            link_ids[node['uuid']] = node_id
        if 'link_id' in node:
            link_ids[node['link_id']] = node_next_id
        link_ids.update(choice_ids)

    print(link_ids)
    for link in data['links']:
        link_callback('Editor', (link_ids[link[0]], link_ids[link[1]]))


def export():
    print('export')

# callback runs when user attempts to connect attributes
def link_callback(sender, app_data):
    # app_data -> (link_id1, link_id2)
    node_from = dpg.get_item_configuration(app_data[0])
    node_to = dpg.get_item_configuration(app_data[1])

    if node_to['label'] != 'ID':
        print('Can link only to ID')
        return

    # if node_from['label'] == 'Next ID':
        # dpg.configure_item(dpg.get_item_children(app_data[0])[1][0], enabled=False)
        # dpg.set_item_source(dpg.get_item_children(app_data[0])[1][0], dpg.get_item_children(app_data[1])[1][0])
    
    dpg.set_item_user_data(app_data[0], {'link_id': app_data[1]})
    dpg.add_node_link(app_data[0], app_data[1], parent=sender)

# callback runs when user attempts to disconnect attributes
def delink_callback(sender, app_data):
    # app_data -> link_id
    attr_1 = dpg.get_item_configuration(app_data)['attr_1']
    attr_2 = dpg.get_item_configuration(app_data)['attr_2']

    print(dpg.get_item_children(attr_1)[1][0])

    # dpg.configure_item(dpg.get_item_children(attr_1)[1][0], enabled=True)
    # dpg.configure_item(dpg.get_item_children(attr_2)[1][0], enabled=True)
    # dpg.set_item_source(dpg.get_item_children(attr_1)[1][0], dpg.get_item_children(attr_1)[1][0])
    # dpg.set_item_source(dpg.get_item_children(attr_2)[1][0], dpg.get_item_children(attr_2)[1][0])

    dpg.delete_item(app_data)

def add_choice(sender, app_data, user_data):
    node_choice = dpg.add_node_attribute(label="Choice", parent=user_data['node'], before=user_data['node_button'], attribute_type=dpg.mvNode_Attr_Output)
    dpg.add_input_text(label="Choice", width=200, parent=node_choice, default_value=user_data.get('value', '') or '')
    return node_choice

def add_node(sender, app_data, pos=None, id=None, nextID=None, type=None, text=None, choices=None):
    node_pos = pos if pos is not None else [200, 200]
    node = dpg.add_node(label="Node", parent="Editor", pos=node_pos)
    node_id = dpg.add_node_attribute(label="ID", parent=node)
    node_next_id = dpg.add_node_attribute(label="Next ID", parent=node, attribute_type=dpg.mvNode_Attr_Output)
    node_choice = dpg.add_node_attribute(label="Choice", parent=node, attribute_type=dpg.mvNode_Attr_Static)
    node_text = dpg.add_node_attribute(label="Text", parent=node, attribute_type=dpg.mvNode_Attr_Static)
    node_button = dpg.add_node_attribute(label="Text", parent=node, attribute_type=dpg.mvNode_Attr_Static)

    input_id = dpg.add_input_text(label="ID", width=200, parent=node_id, default_value=id or '')
    input_next_id = dpg.add_input_text(label="Next ID", width=200, parent=node_next_id, default_value=nextID or '')
    input_type = dpg.add_combo(label='Type', items=TYPES, width=200, parent=node_choice, default_value=type or '')
    input_text = dpg.add_input_text(label="Text", multiline=True, width=200, height=150, parent=node_text, default_value=text or '')

    choice_ids = {}
    if choices:
        for choice in choices:
            choice_ids[choice['id']] = add_choice(None, None, {'node': node, 'node_button': node_button, 'value': choice['text']})

    dpg.add_button(label='+', width=200, parent=node_button, callback=add_choice, user_data={'node': node, 'node_button': node_button})

    return node_id, node_next_id, choice_ids

with dpg.window(tag="Primary Window", width=400, height=400):
    with dpg.node_editor(tag="Editor", callback=link_callback, delink_callback=delink_callback):
        pass


with dpg.font_registry():
    with dpg.font("Roboto-Regular.ttf", size=16, default_font=True) as font:
        dpg.add_font_range_hint(dpg.mvFontRangeHint_Cyrillic)
        dpg.bind_font(font)

# dpg.show_documentation()
# dpg.show_font_manager()
# dpg.show_item_registry()
# dpg.setup_registries()
dpg.create_viewport(title='Editor', width=800, height=600)
with dpg.viewport_menu_bar():
    with dpg.menu(label='File'):
        dpg.add_menu_item(label="Save", callback=save)
        dpg.add_menu_item(label="Load", callback=load)
        dpg.add_menu_item(label="Export", callback=export)
    dpg.add_menu_item(label="New", callback=add_node)
dpg.setup_dearpygui()
dpg.show_viewport()
dpg.set_primary_window("Primary Window", True)
dpg.start_dearpygui()
dpg.destroy_context()
