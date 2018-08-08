import os

network=[];
links={};

def addnode(node):
    # print("adding", node);
    if node in links:
        return
    links[node]=[];

def addlink(node1, node2):
    # print("adding link bw",node1,node2);
    if node1 in links:
        links[node1].append(node2)
    else:
         links[node1]=[node2]

    if node2 in links:
        links[node2].append(node1)
    else:
        links[node2]=[node1]

def remlink(node1,node2):
    # print("removing link bw ",node1,node2);
    links[node1].remove(node2);
    links[node2].remove(node1);

def delnode(node1):
    # print("deleting node",node1);
    for i in links[node1]:
        links[i].remove(node1)
    links.pop(node1,None);






x=input().split();
n=int(x[0])
op=int(x[1])

for i in range(0,op):
    operation=input().split();
    if(operation[0]=="addnode"):
        node1=int(operation[1]);
        addnode(node1);

    if(operation[0]=="addlink"):
        node1=int(operation[1])
        node2=int(operation[2])
        addlink(node1,node2);

    if(operation[0]=="delnode"):
        node1=int(operation[1])
        delnode(node1);

    if(operation[0]=="remlink"):
        node1=int(operation[1])
        node2=int(operation[2])
        remlink(node1,node2);

q=int(input());
for i in range(0,q):
    t=int(input());
    if t in links:
        if len(links[t])==0:
            print("no connections")
        else:
            for i in links[t]:
                print(i,end=' ')
            print()
    else:
        print("not in network")
