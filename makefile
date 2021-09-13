all : makes makec
makes :
	gcc -Wall -pthread "diffuseur.c" -o "Diffuseur"
	gcc -Wall "clientmulti.c" -o "clientmulti"
	javac *.java

makec :
	gcc -Wall -pthread "clientfinal.c" -o "Utilisateur"


clean :
	rm *.class

reset :
	rm -f "Diffuseur" "Utilisateur" "gestionnaire.txt"


