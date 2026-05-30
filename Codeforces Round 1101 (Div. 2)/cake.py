import sys
data=sys.stdin.read().split()
if data:
 outputs=[];index=1
 for tests in range(int(data[0])):
  length=int(data[index]);index+=1;total=0;minimum=9e18;answers=[]
  for position in range(1,length+1):
   total+=int(data[index]);index+=1;height=total//position
   if height<minimum:minimum=height
   answers.append(str(minimum))
  outputs.append(" ".join(answers))
 sys.stdout.write("\n".join(outputs)+"\n")
