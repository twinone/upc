import random
import subprocess

plats = 20
primers = 10
incompatibles = 4
restricciones = 4
mincal = 300
maxcal = 1200

minpreu = 3
maxpreu = 15

cal = []
preu = []

tipus = ["peix", "sopa", "carn", "pasta", "arroz", "fruta", "vegetales", "pure", "pan"]
dies = ["lu", "ma", "mi", "ju", "vi"]

f = open('test.pddl', 'w')
f.write("(define (problem menu1)\n")
f.write("(:domain menu)\n")
f.write("(:objects ")
for item in dies:
	f.write(item+" ")
f.write("- dia ")
for item in tipus:
	f.write(item+" ")
f.write("- tipus ")
for i in range(primers):
  f.write("p"+str(i)+" ")
  cal.append(str(random.randint(mincal, maxcal)))
  preu.append(str(random.randint(minpreu, maxpreu)))
f.write("- primer ")
for i in range(plats-primers):
  f.write("p"+str(i+primers)+" ")
  cal.append(str(random.randint(mincal, maxcal)))
  preu.append(str(random.randint(minpreu, maxpreu)))
f.write("- segon)\n")
f.write("(:init ")
f.write("(diainici lu) (seguent lu ma) (seguent ma mi) (seguent mi ju) (seguent ju vi) ")
for i in range(incompatibles):
	f.write("(incompatible p"+str(random.randint(0, primers-1))+" p"+str(random.randint(primers, plats-1))+") ")
for i in range(restricciones):
	f.write("(restriccio "+random.choice(dies)+" p"+str(random.randint(0, plats-1))+") ")
for i in range(plats):
	if i < primers:
		f.write("(primer p"+str(i)+" "+random.choice(tipus)+") ")
	else:
		f.write("(segon p"+str(i)+" "+random.choice(tipus)+") ")
f.write("\n")
f.write("(= (total-preu) 0) ")
for i in range(plats):
	f.write("(= (calories p"+str(i)+") "+cal.pop()+") ")
f.write("\n")
for i in range(plats):
	f.write("(= (preu p"+str(i)+") "+preu.pop()+") ")
f.write("\n")

f.write(")\n")
f.write("(:goal (and (diac lu) (diac ma) (diac mi) (diac ju) (diac vi)))\n")
f.write("(:metric minimize (total-preu))\n")
f.write(")")
f.close()