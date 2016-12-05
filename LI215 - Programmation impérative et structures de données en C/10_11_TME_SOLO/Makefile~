#Pour compiler sur une machine de l'ARI
#Mettre a jour le repertoire ABR
ABR_DIR = ./
C_FLAGS = -Wall -g 

all : schema

abr.o : ${ABR_DIR}abr.c ${ABR_DIR}abr.h
	gcc -I${ABR_DIR} ${C_FLAGS} -c ${ABR_DIR}abr.c

geom.o : geom.c geom.h ${ABR_DIR}abr.h
	gcc -I${ABR_DIR} ${C_FLAGS} -c geom.c

schema.o :schema.c
	gcc -I${ABR_DIR} ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c schema.c

schema_callback.o : schema_callback.c geom.h ${ABR_DIR}abr.h
	gcc -I${ABR_DIR} ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c schema_callback.c

schema : schema.o schema_callback.o geom.o abr.o
	gcc -I${ABR_DIR} ${C_FLAGS} -o schema schema.o schema_callback.o geom.o abr.o `pkg-config --libs gtk+-2.0`

clean :
	rm -f *.o schema
