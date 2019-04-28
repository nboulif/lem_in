import lem_global as lg

from vpython import color
from vpython import vector
from vpython import ring
from vpython import cylinder
from vpython import text
from vpython import sphere

from math import cos
from math import sin
from math import pi

from datetime import datetime

def make_tree_node(reinit=False):    
    x = 0
    y = 0
    z = 0
        
    node_next_lvl = []
    node_done = []
    
    # lg.start_node["node"].pos = vector(x, y, z)
    lg.start_node["o_pos_v2"] = vector(x, y, z)
    if not reinit:
        lg.all_rings.append(ring(visible=False, 
                pos=vector(x, y, z), 
                axis=vector(x, y, z + 1), 
                opacity=0.2,
                thickness=0.3, 
                radius=lg.radius_ring, 
                color=color.white)
            )
    else:
        lg.all_rings[0].radius = lg.radius_ring
    
    z += lg.dist_ring

    #node_done.append(lg.start_node["name"])
    lg.start_node["visited"] = 1
    now = datetime.now()
    for link in lg.start_node["links"]:
        if link["node1"]["name"] == lg.start_node["name"]:
            node_next_lvl.append(link["node2"])
            link["node2"]["visited"] = 1
            #node_done.append(link["node2"]["name"])
        else:
            node_next_lvl.append(link["node1"])
            link["node1"]["visited"] = 1
            #node_done.append(link["node1"]["name"])
    print(f"link {datetime.now() - now}")
    lvl = 1
    while(node_next_lvl):
        node_current_level = [i for i in node_next_lvl]
        # print("{}".format([i["name"] for i in node_current_level]))
        if not reinit:
            lg.all_rings.append(ring(visible=False, 
                pos=vector(0, 0, z), 
                axis=vector(0, 0, z + 1), 
                opacity=0.2,
                thickness=0.3, 
                radius=lg.radius_ring, 
                color=color.white)
            )
        else:
            lg.all_rings[lvl].radius = lg.radius_ring
            lg.all_rings[lvl].pos=vector(0, 0, z)
            lg.all_rings[lvl].axis=vector(0, 0, z + 1)
        lvl += 1
        step = len(node_current_level)
        if step > 1:
            alpha = 0.0
            indice = 0
            # print("{}".format(step))
            while (alpha < 360):
                # print("indice {} alpha {}".format(indice, alpha))
                alpha2 = alpha * (pi / 180)
                x2 = x + lg.radius_ring_node * cos(alpha2)    
                y2 = y + lg.radius_ring_node * sin(alpha2)
                # node_current_level[indice]["text"].pos = vector(x2, y2, z)
                # node_current_level[indice]["node"].pos = vector(x2, y2, z)
                node_current_level[indice]["o_pos_v2"] = vector(x2, y2, z)
                alpha += 360 / step + 0.0000000000001
                indice += 1
                # print(alpha2)
        else:
            # node_current_level[0]["node"].pos = vector(0, 0, z)
            node_current_level[0]["o_pos_v2"] = vector(0, 0, z)


        now = datetime.now()
        node_next_lvl = []
        for node in node_current_level:
            for i in node["links"]:
                if i["node1"]["name"] == node["name"] and not i["node2"]["visited"]:
                    node_next_lvl.append(i["node2"])
                    i["node2"]["visited"] = 1
                    #node_done.append(i["node2"]["name"])
                elif not i["node1"]["visited"]:
                    node_next_lvl.append(i["node1"])
                    i["node1"]["visited"] = 1
                    #node_done.append(i["node1"]["name"])
        print(f"bfs{datetime.now() - now}")
        z += lg.dist_ring


    # for edge_name, edge in lg.all_edges.items():
    #     edge["edge"].pos = edge["node1"]["node"].pos
    #     edge["edge"].axis = edge["node2"]["node"].pos - edge["node1"]["node"].pos


def init_all_path_node():

    all_path_sep = []
    for ant_move in lg.all_path[0].split(' '):
        tmp = [lg.start_node]

        first_ant_id, ttt= ant_move.split('-')
        for path in lg.all_path:
            
            if first_ant_id not in path:
                break
            all_move = path.split(' ')
            for move in all_move:
                if first_ant_id in move:
                    tmp.append(lg.all_nodes[move.strip().split('-')[1]])
                    break
        tmp.append(lg.end_node)
        all_path_sep.append(tmp)
    all_color = [color.green, color.red, color.yellow, color.blue, color.purple, color.cyan]

    for count, path_sep in enumerate(all_path_sep):
        
        for i in range(len(path_sep)):
            try:
                cur_node = path_sep[i]

                next_node = path_sep[i + 1]

                try:
                    link = lg.all_edges[cur_node["name"]+"-"+next_node["name"]]
                except:
                    link = lg.all_edges[next_node["name"]+"-"+cur_node["name"]]
                link["color2"] = all_color[count] * 4
                link["opacity1"] = 0.5  
                link["opacity2"] = 0.2
            except Exception:
                pass
                # print("ERROR init -> {}".format(e))

def parse(f, reinit=False):
    try:
        lg.nb_ants = int(f.readline())
    except Exception as e:
        print(e)
        return None
    command = 0
    
    start_offset = 0

    line = f.readline()
    while line:
        line = str(line).replace('\n', '')
        if len(line) == 0:
            line = f.readline()
            continue
        if line[0] == '#':
            if line[1] == '#' and ("start" in line or "end" in line):
                command = 1 if "start" in line else 2
                while line and (line[0] == '#'):
                    line = f.readline()
                continue
            else:
                pass
        elif line[0] == 'L':
            while line and line[0] == 'L':
                if (line.strip().replace('\n', '')):
                    lg.all_path.append(line.strip().replace('\n', ''))
                line = f.readline()
            break
        elif '-' in line:
            nodes = line.split('-')
            lg.all_edges[line.strip()] = {"name":line, "color1":color.white, "node1": lg.all_nodes[nodes[0]], "node2": lg.all_nodes[nodes[1]]}
            lg.all_nodes[nodes[0]]["links"].append(lg.all_edges[line.strip()])
            lg.all_nodes[nodes[1]]["links"].append(lg.all_edges[line.strip()])
        
        else:
            tmp = line.split(' ')
            try:
                node_pos_x = (int(tmp[1]))
                node_pos_y = (int(tmp[2]))
                lg.all_nodes[tmp[0]] = {}
                lg.all_nodes[tmp[0]]["o_pos_v1"] = vector(start_offset + node_pos_x, start_offset + node_pos_y, 0)
                lg.all_nodes[tmp[0]]["name"] = tmp[0]
                lg.all_nodes[tmp[0]]["visited"] = 0
                lg.all_nodes[tmp[0]]["color"] = color.white
                lg.all_nodes[tmp[0]]["links"] = []
                lg.nb_nodes +=1
                if command:
                    if command == 1: lg.start_node = lg.all_nodes[tmp[0]]
                    if command == 2: lg.end_node = lg.all_nodes[tmp[0]]
                    command = 0
            except Exception as e:
                print(e)
                return(False)
        if line:
            line = f.readline()
    lg.start_node["color"] = color.blue
    lg.end_node["color"] = color.red
    init_all_path_node()
    make_tree_node()
    return (True)