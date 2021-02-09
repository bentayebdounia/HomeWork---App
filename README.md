# HW1 
Ce programme calcule la multiplication de deux matrices carrées en parallele en utilisant p threads 
dans ce programme il y'a 3 versions de calcule parallele :
la version_1 : c'est de partitionner les ligne (ou les colomns ) de la matrice résultat C à p threads .
la version_2 : c'est de partitionner la matrice résultat C à des blocks de meme ligne et colomn à p threads .
la version_3 : c'est de partitionner la matrice résultat C à des blocks de n/2 lignes et n/(p/2) colomns à p threads .

