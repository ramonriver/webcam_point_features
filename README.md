# webcam_point_features
Detection of ORB features from online webcam imges.

Explicació de l'algoritme ORB:
ORB és un algoritme per detectar i caracteritzar punts claus en imatges. Aquest és una combinació de l'algoritme FAST (detector de punts clau) i el BRIEF (descriptiu).

Per la detecció de punts clau, calcula la intensitat del punts on hi ha una cantonada i els dóna una orientació a partir d'un vector. Aquest vector el defineix des del centre del punt fins a la zona de més pes de la regió circular de radi r que marca.

Per a la caracterització, utilitza la descripció BRIEF i després la "gira". És a dir, primer fa un conjunt de proves binàries n al punt (x,y) per definir una matriu 2 x n, S, que conté les coordenades d'aquests pixels. Després, amb l'orientació de la regió, theta, obté la matriu de rotació i "gira" la matriu S, per obtenir Stheta. 

A partir del conjunt de punts clau de Stheta correctes, es calcula la seva caracteritzacio. També es construeix una taula de referència amb models BRIEF precalculats, discretitzant l'angle en increments de 2*PI/30 rad.

A més, l'algoritme ORB fa una recerca de les proves binàries que tenen més variació, una mitjana al voltant de 0.5 i no són correlatives. Això és perquè amb més variació hi ha més discriminació i, per tant, més diferència en la resposta a les entrades. També, si no són correlatives, cada prova contribuirà en el resultat final de forma més notòria.

Referències:
https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_feature2d/py_orb/py_orb.html

https://stackoverflow.com/questions/38767703/orb-feature-descriptor-official-paper-explanation

