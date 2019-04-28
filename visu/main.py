import lem_global as lg

from vpython import scene
from lem_parse import parse

import threading

from vpython import sphere
from vpython import ring
from vpython import box
from vpython import cylinder
from vpython import text
from vpython import vector
from vpython import color
from datetime import datetime
import sys


def update_caption():

    scene.caption = f"""
Data :
(1/2/3)current view =  {lg.current_view}

(p) paused = {lg.paused}

(q/w)time for one move = {lg.time_one_move}

(u/j) distance between nodes (view 1) = {lg.dist}
(i/k) distance between each lvl (view 2 & 3) = {lg.dist_ring}
(o/l) radius/dist between nodes (view 2 & 3) = {lg.radius_ring_node}
(o/l) radius rings (view3) = {lg.radius_ring}
(y/h) all together

"""
    from vpython import button

    from lem_move import move_ants
    button(bind=move_ants, text='Move Ants')
    scene.append_to_caption('\n\n')

    from lem_path import show_all_path_node
    button(bind=show_all_path_node, text='SHOW PATHS')
    scene.append_to_caption('\n\n')
        
def key_handler(e):
    if e.key == 'q':
        if lg.time_one_move < 3:
           lg.time_one_move += 0.1
    elif e.key == 'w': 
        if lg.time_one_move > 0.19:
            lg.time_one_move -= 0.1
    elif e.key in "yhujikol":
        if e.key == 'u':
            lg.dist += 1
        elif e.key == 'j':
            if lg.dist > 5:
                lg.dist -= 1
        elif e.key == 'i':
            lg.dist_ring += 1
        elif e.key == 'k':
            if lg.dist_ring > 5:
                lg.dist_ring -= 1
        elif e.key == 'o':
             lg.radius_ring_node += 1
             lg.radius_ring += 1
        elif e.key == 'l':
            if lg.radius_ring_node > 5:
                lg.radius_ring_node -= 1
                lg.radius_ring -= 1
        elif e.key == 'y':
            lg.dist += 1
            lg.dist_ring += 1
            lg.radius_ring += 1
            lg.radius_ring_node += 1
        else :
            if lg.dist > 5:
                lg.dist -= 1
            if lg.dist_ring > 5:
                lg.dist_ring -= 1
            if lg.radius_ring_node > 5:
                lg.radius_ring_node -= 1
                lg.radius_ring -= 1
        
    elif e.key == 'p':
        lg.paused = -lg.paused 
    elif e.key == '1':
        lg.current_view = 1
    elif e.key == '2':
        lg.current_view = 2
    elif e.key == '3':
        lg.current_view = 3
    elif e.key == '+':
        lg.n_ant += 1
    elif e.key == '-':
        lg.n_ant -= 1
    elif e.key == 'v':
        lg.vision_ant = 1 - lg.vision_ant
    elif e.key == 'r':
        scene.camera.pos = vector(0, 0, 0)
        scene.camera.axis = vector(0, 1, 0)
    elif e.key == 'esc':
        exit()

    if e.key in "yhujikol123v":
        from lem_parse import make_tree_node
        make_tree_node(True)
        generate_view(lg.current_view)
    update_caption()


vcube = vector(2, 2, 2)

def draw_nodes(nodes_name, v, i):
    now = datetime.now()
    try:
        for node_name in nodes_name:
            if v == 1:
                o_pos = lg.all_nodes[node_name]["o_pos_v1"]
            else :
                o_pos = lg.all_nodes[node_name]["o_pos_v2"]
            try:
                lg.all_nodes[node_name]["node"]
            except:
                # lg.all_nodes[node_name]["node"] = sphere(visible = True)
                lg.all_nodes[node_name]["node"] = box(visible = True, size=vcube)
                # lg.all_nodes[node_name]["text"] = text(visible = False, text=node_name, color=color.white)

            
            if v == 1:
                lg.all_nodes[node_name]["node"].pos = lg.dist * o_pos
            else :
                lg.all_nodes[node_name]["node"].pos = o_pos

            # lg.all_nodes[node_name]["text"].pos = lg.all_nodes[node_name]["node"].pos
            # lg.all_nodes[node_name]["text"].pos.y += 1
            lg.all_nodes[node_name]["node"].opacity = 0.5
            lg.all_nodes[node_name]["node"].color = lg.all_nodes[node_name]["color"]
            # lg.all_nodes[node_name]["node"].radius = 2
    except Exception as e:
        print(f"ERRRRRROR {e}")
    print(f"Finish nodes {i} {datetime.now() - now}")


def draw_edges(edges_name, v, i):
    now = datetime.now()
    try:   
        for edge_name in edges_name:
            try:
                lg.all_edges[edge_name]["edge"]
            except:
                lg.all_edges[edge_name]["edge"] = cylinder(visible = True)
        

            lg.all_edges[edge_name]["edge"].pos = lg.all_edges[edge_name]["node1"]["node"].pos

            lg.all_edges[edge_name]["edge"].axis = lg.all_edges[edge_name]["node2"]["node"].pos - lg.all_edges[edge_name]["node1"]["node"].pos

            lg.all_edges[edge_name]["edge"].opacity = 0.5
            lg.all_edges[edge_name]["edge"].radius = 1
            lg.all_edges[edge_name]["edge"].color = lg.all_edges[edge_name]["color1"]
    except Exception as e:
        print(f"ERRRRRROR {e}")
    print(f"Finish edges {i} {datetime.now() - now}")



def generate_view(v):
    lg.wait_text.visible = True
    max_thread = 20

    all_list_nodes = []
    for i in range(max_thread):
        all_list_nodes.append([])
    i = 0
    for node_name, node in lg.all_nodes.items():
        all_list_nodes[i].append(node_name)
        i += 1
        if i == max_thread:
            i = 0
        

    max_thread = 20

    all_list_edges = []
    for i in range(max_thread):
        all_list_edges.append([])
    i = 0
    for edge_name, node in lg.all_edges.items():
        all_list_edges[i].append(edge_name)
        i += 1
        if i == max_thread:
            i = 0

    max_thread = 20

    all_threads_nodes = []
    for i in range(max_thread):
        all_threads_nodes.append(threading.Thread(target=draw_nodes, args=(all_list_nodes[i],v,i,)))
        all_threads_nodes[i].start()
        #all_threads_nodes.append(t)
        #threading.Thread(target=draw_nodes, args=(all_list_nodes[i],v,)).start
    for thread in all_threads_nodes:
        thread.join()
    print(f"Finish nodes all_nodes")

    max_thread = 20

    all_threads_edges = []
    for i in range(max_thread):
        all_threads_edges.append(threading.Thread(target=draw_edges, args=(all_list_edges[i],v,i,)))
        all_threads_edges[i].start()
        #threading.Thread(target=draw_edges, args=(all_list_edges[i],v,)).start
        #all_threads_edges.append(t)
    for thread in all_threads_edges:
        thread.join()
    print(f"Finish nodes all_edges")

    #for node_name, node in lg.all_nodes.items():
    #    lg.all_nodes[node_name]["node"].visible = True
    #    lg.all_nodes[node_name]["text"].visible = True
    #for edge_name, node in lg.all_edges.items():
    #    lg.all_edges[edge_name]["edge"].visible = True
    if v == 3:
        for aring in lg.all_rings:
            aring.visible = True
    else:
        for aring in lg.all_rings:
            aring.visible = False

    lg.wait_text.visible = False

def main():

    if len(sys.argv) != 2:
        print("WRONG NB FILES")
        exit(0)

    lg.init()

    f = open(str(sys.argv[1]), "r")
    if not parse(f):
        print("PARSE PB")
        exit(0)
    f.close()
    print(f"len all_nodes => {len(lg.all_nodes)}")
    print(f"len all_edges => {len(lg.all_edges)}")
    def move_camera(ev):
        if ev.event == "mousedown":
            lg.cur_camera_pos = ev.pos
        elif ev.event == "mousemove":
            scene.camera.pos -= (ev.pos - lg.cur_camera_pos ) / 20

    scene.bind('mouseup mousemove mousedown', move_camera)

    scene.bind('keydown', key_handler)

    lg.wait_text = text(height=10, visible=False, text="Generating Map...", color=color.orange, billboard=True, emissive=True)
    lg.current_view = 2
    generate_view(2)

    update_caption()

if __name__ == "__main__":

    main()
    

    


