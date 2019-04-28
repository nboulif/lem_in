
class VPUtils():

    def __init__(self, base_scene, title, width, height, background_color):
        base_scene.title = title

        base_scene.width = width
        base_scene.height = height

        base_scene.background = background_color

def init():
    global all_nodes
    global all_edges
    global all_rings
    global all_ants
    global all_path
    global all_path_nodes
    global nb_nodes
    global nb_ants
    global start_node
    global end_node
    global dist
    global time_one_move
    global paused
    global cur_camera_pos
    global wait_text
    global n_ant
    global current_view
    global vision_ant

    global dist_ring
    global radius_ring
    global radius_ring_node

    from vpython import scene
    from vpython import color
    from vpython import text

    VPUtils(scene, "Visu Lem-in", 1200, 1200, color.black)

    all_nodes = {}
    all_edges = {}
    all_rings = []
    
    all_ants = []
    all_path = []
    
    all_path_nodes = []
    
    nb_nodes = 0
    nb_ants = 0
    n_ant = 0
    vision_ant = 0
    dist_ring = 10
    radius_ring_node = 10
    radius_ring = radius_ring_node + 10

    dist = 10

    paused = -1
    time_one_move = 0.5

