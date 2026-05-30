I=input
for _ in range(int(I())):
 sixseven=int(I());a=list(map(int,I().split()))
 print(min(max(sum(v<u for v in a),sum(v>u for v in a))for u in set(a)))
