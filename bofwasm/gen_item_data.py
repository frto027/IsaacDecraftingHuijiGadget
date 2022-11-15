import xml.etree.ElementTree as ET

itempool = r'E:\SteamLibrary\steamapps\common\The Binding of Isaac Rebirth\resources-dlc3\itempools.xml'
items_metadata = r'E:\SteamLibrary\steamapps\common\The Binding of Isaac Rebirth\resources-dlc3\items_metadata.xml'
items = r'E:\SteamLibrary\steamapps\common\The Binding of Isaac Rebirth\resources-dlc3\items.xml'
with open(itempool,'rb') as f:
    itempool = f.read().decode('utf8')

itempool = ET.fromstring(itempool)

assert itempool.tag == 'ItemPools'

output = ''

pools_gen = {
    "treasure":0,
    "shop":1,
    "boss":2,
    "devil":3,
    "angel":4,
    "secret":5,
    "shellGame":7,
    "goldenChest":8,
    "redChest":9,
    "curse":12,
    "planetarium":26,
}


output += """
struct ItemPoolDataItem{
    int id;float weight;
};
struct ItemPoolMetaData{
    int index, length;
};
struct ItemPoolData{
    struct ItemPoolDataItem * datas;
    int length;
};

struct ItemConfigData{
    int aid,quality;
};
"""


output_item_pool_datas = "ItemPoolDataItem item_pool_datas[] = {\n"

item_pool_metadata = {} # [pool_id] = {index,length}

output_array_index = 0

for pool in itempool:
    assert pool.tag == "Pool"
    poolname = pool.attrib['Name']
    if poolname in pools_gen:
        # output += f"{pools_gen[poolname]}:["
        item_pool_metadata[pools_gen[poolname]] = {
            "index":output_array_index,
            "length":len(pool)
        }
        for item in pool:
            assert item.tag == "Item"
            output_item_pool_datas += "    {" + f"{item.attrib['Id']},{item.attrib['Weight']}" + "},\n"
            output_array_index += 1
output_item_pool_datas += "};\n"

output += output_item_pool_datas


# metadata
output += """
ItemPoolMetaData item_pool_metadata[] = {
"""
for i in range(max(item_pool_metadata.keys())+1):
    if i in item_pool_metadata:
        output += "    {%d,%d},\n" % (item_pool_metadata[i]["index"],item_pool_metadata[i]["length"])
    else:
        output += "    {-1,-1},\n"
output += "};\n"

output += """

ItemPoolData GetItemPoolData(int item_pool_id){
    int index = item_pool_metadata[item_pool_id].index;
    if(index < 0){
        return {NULL, 0};
    }else{
        return {&item_pool_datas[index], item_pool_metadata[item_pool_id].length};
    }
}

"""

item_configs = {}

for i in range(734):
    item_configs[str(i)] = {"aid":'-1',"quality":-1}

with open(items, 'rb') as f:
    items = f.read().decode('utf8')
items = ET.fromstring(items)
assert items.tag == 'items'
for item in items:
    if item.tag in ['passive', 'familiar','active']:
        if 'achievement' in item.attrib:
            item_configs[item.attrib['id']]["aid"] =item.attrib['achievement']


with open(items_metadata, 'rb') as f:
    items_metadata = f.read().decode('utf8')
items_metadata = ET.fromstring(items_metadata)
assert items_metadata.tag == 'items'

for item in items_metadata:
    if item.tag == 'item' :
        item_configs[item.attrib['id']]["quality"]= item.attrib['craftquality'] if 'craftquality' in item.attrib else item.attrib['quality']

output += "struct ItemConfigData item_config_datas[] = {\n"

for i in range(len(item_configs)):
    output += "    {%s,%s},\n" % (item_configs[str(i)]['aid'],item_configs[str(i)]['quality'])
output += "};\n"

output += """

struct ItemConfigData* GetItemConfig(int item_id){
    return &item_config_datas[item_id];
}

"""

# with open(items_metadata, 'rb') as f:
#     items_metadata = f.read().decode('utf8')
# items_metadata = ET.fromstring(items_metadata)
# assert items_metadata.tag == 'items'


# item_id_aid = {}
# with open(items, 'rb') as f:
#     items = f.read().decode('utf8')
# items = ET.fromstring(items)
# assert items.tag == 'items'
# for item in items:
#     if item.tag in ['passive', 'familiar','active']:
#         if 'achievement' in item.attrib:
#             assert not item.attrib['id'] in item_id_aid
#             item_id_aid[item.attrib['id']] = item.attrib['achievement']
#     else:
#         assert item.tag in ['trinket', 'null']


# with open(items_metadata, 'rb') as f:
#     items_metadata = f.read().decode('utf8')
# items_metadata = ET.fromstring(items_metadata)
# assert items_metadata.tag == 'items'

# output += "let item_config_data = {"
# if prettyprint:
#     output += "\n"

# for item in items_metadata:
#     if item.tag == 'item' :
#         if prettyprint:
#             output += "    "
#         output += item.attrib['id'] + ':{quality:' + item.attrib['quality'] 

#         if item.attrib['id'] in item_id_aid:
#             output += ',achievement_id:'+item_id_aid[item.attrib['id']]

#         output += '},'
#         if prettyprint:
#             output += "\n"
# output += "}\n"




# output += """
# module.exports = {
#     item_pool_data:item_pool_data,
#     item_config_data:item_config_data
# }
# """


with open('item_data.h','wb') as f:
    f.write(output.encode('utf8'))
