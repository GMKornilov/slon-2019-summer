import networkx as nx
import matplotlib.pyplot as plt
from networkx.drawing.nx_agraph import write_dot, graphviz_layout

def dfs(v, graph, g, used):
    used[v] = True
    for i in g[v]:
        if not used[i]:
            graph.add_node(i)
            graph.add_edge(v, i)
            dfs(i, graph, g, used)

s = input()
n = 0
for ch in s:
    if ch == '[':
        n += 1
g = [[] for i in range(n)]
used = [False for i in range(n)]
st = list()
i = -1
for ch in s:
    if ch == ' ' or ch == ',':
        continue
    if ch == ']':
        st.pop(-1)
    else:
        i += 1
        if len(st) > 0:
            g[st[-1]].append(i)
        st.append(i)

G = nx.DiGraph()

G.add_node(0)
dfs(0, G, g, used)

#write_dot(G, 'graph.dot')

pos = graphviz_layout(G, prog='dot') 
nx.draw(G, pos, with_labels=False, font_weight='bold', arrows=False)
plt.savefig("g.svg")
plt.show()


