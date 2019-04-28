import lem_global as lg

from vpython import sphere
from vpython import vector
from vpython import color
from vpython import scene


import threading
import time
from datetime import datetime

def move_one_ant(ant_id, next_node_name, indice_thread, nb_ants):
    step = 50
    time_2_sleep = lg.time_one_move / step

    cur_node = lg.all_ants[ant_id - 1]["node"]

    next_node = lg.all_nodes[next_node_name]
    try:
        link = lg.all_edges[cur_node["name"]+"-"+next_node["name"]]
    except:
        link = lg.all_edges[next_node["name"]+"-"+cur_node["name"]]

    link["edge"].color = link["color2"]
    link["edge"].opacity = link["opacity2"]
    pos = vector(0, 0, 0)
    if indice_thread == lg.n_ant % nb_ants and lg.vision_ant:
        ant = sphere(pos=pos, color=lg.all_ants[ant_id - 1]["color"], opacity=0, radius=0.5)
    else:
        ant = sphere(pos=pos, color=lg.all_ants[ant_id - 1]["color"], opacity=1, radius=0.5)
    
    for i in range(step):
        now = datetime.now()
        while lg.paused > 0:
            time.sleep(0.1)
        # pos_x = cur_node["node"].pos.x + (next_node["node"].pos.x - cur_node["node"].pos.x) * (i / step)
        # pos_y = cur_node["node"].pos.y + (next_node["node"].pos.y - cur_node["node"].pos.y) * (i / step)
        # pos_z = cur_node["node"].pos.z + (next_node["node"].pos.z - cur_node["node"].pos.z) * (i / step)
        # pos = vector(pos_x, pos_y, pos_z)
        # local_light(pos=pos, color=lg.all_ants[ant_id - 1]["color"])
        # ant.pos = pos
        # if indice_thread == 0:
        try:
            ant.pos = cur_node["node"].pos + (next_node["node"].pos - cur_node["node"].pos) * (i / step)
            if indice_thread == lg.n_ant % nb_ants and lg.vision_ant:
                scene.camera.pos = ant.pos
                scene.camera.axis = (next_node["node"].pos - cur_node["node"].pos)
        except Exception as e:
            print(f"CAM FAILLL {e}")
    
                
        time.sleep(time_2_sleep)
        # lamp.visible = False
    ant.visible = False
    
    link["edge"].color = link["color1"]
    link["edge"].opacity = link["opacity1"]
    
    lg.all_ants[ant_id - 1]["node"] = next_node

def move_ants():

    all_color = [color.red, color.yellow, color.blue, color.purple, color.cyan]
    
    lll = len(lg.all_path[0].split(' '))
    if (lll < len(all_color)):
        all_color = all_color[:lll]
        lg.all_ants = [{"node" : lg.start_node, "color" : all_color[i % lll]} for i in range(lg.nb_ants)]
    else:
        lg.all_ants = [{"node" : lg.start_node, "color" : color.red} for i in range(lg.nb_ants)]
    
    for line in lg.all_path:
        all_ants_move = line.split(' ')
        threads = []
        i = 0
        for ant_move in all_ants_move:
            ant_id, next_node_name = ant_move.split('-')
            t = threading.Thread(target=move_one_ant, args=(int(ant_id[1:]), next_node_name, i, len(all_ants_move),))
            threads.append(t)
            t.start()
            i += 1
        #for t in threads:
        #    t.start()
        
        for t in threads:
            t.join()
