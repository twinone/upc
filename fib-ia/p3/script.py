import random
import subprocess

plats = 50
primers = 25
mincal = 300
maxcal = 1200
cal = []

tipus = ["peix", "sopa", "carn", "pasta", "arroz", "fruta", "vegetales", "pure", "pan"]

f = open('test.pddl', 'w')
f.write("(define (problem menu1)\n")
f.write("(:domain menu)\n")
f.write("(:objects lu ma mi ju vi - dia ")
for item in tipus:
	f.write(item+" ")
f.write("- tipus ")
for i in range(primers):
  f.write("p"+str(i)+" ")
  cal.append(str(random.randint(mincal, maxcal)))
f.write("- primer ")
for i in range(plats-primers):
  f.write("p"+str(i+primers)+" ")
  cal.append(str(random.randint(mincal, maxcal)))
f.write("- segon)\n")
f.write("(:init ")
for i in range(plats):
	if i < primers:
		f.write("(primer p"+str(i)+" "+random.choice(tipus)+") ")
	else:
		f.write("(segon p"+str(i)+" "+random.choice(tipus)+") ")
f.write("\n")
f.write("(= (total-cal) 0) ")
for i in range(plats):
	f.write("(= (calories p"+str(i)+") "+cal.pop()+") ")
f.write("\n")
f.write("(diainici lu) (seguent lu ma) (seguent ma mi) (seguent mi ju) (seguent ju vi)")
f.write(")\n")
f.write("(:goal (and (diac lu) (diac ma) (diac mi) (diac ju) (diac vi)))\n")
f.write("(:metric minimize (total-cal))\n")
f.write(")")
f.close()