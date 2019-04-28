import lem_global as lg

import time

def show_all_path_node():

    all_path_sep = []


    for ant_move in lg.all_path[0].split(' '):
        tmp = [lg.start_node]

        first_ant_id, ttt = ant_move.split('-')
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


    for path_sep in all_path_sep:
        
        for i in range(len(path_sep)):
            try:
                cur_node = path_sep[i]

                next_node = path_sep[i + 1]

                try:
                    link = lg.all_edges[cur_node["name"]+"-"+next_node["name"]]
                except:
                    link = lg.all_edges[next_node["name"]+"-"+cur_node["name"]]
                link["edge"].color = link["color2"]
                link["edge"].opacity = link["opacity2"]
            except Exception:
                pass
                # print("ERROR -> {}".format(e))

    time.sleep(10)
    
    for path_sep in all_path_sep:
    
        for i in range(len(path_sep)):
            try:
                cur_node = path_sep[i]

                next_node = path_sep[i + 1]

                try:
                    link = lg.all_edges[cur_node["name"]+"-"+next_node["name"]]
                except:
                    link = lg.all_edges[next_node["name"]+"-"+cur_node["name"]]

                link["edge"].color = link["color1"]
                link["edge"].opacity = link["opacity1"]
            except Exception:
                pass
                # print("ERROR -> {}".format(e))
