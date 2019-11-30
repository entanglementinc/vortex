 # coding=utf-8
import sys
import CramerShoup
import Hash
import codecs



while 1:
    print('\n')
    print("***************************       MENU PRINCIPAL        ****************************************************************")
    print("Souhaitez vous:", "ThreeFish (Press 1) ", "Cramer-Shoup (Press 2)",
          "Hashage (Press 3)","Exit (press 4)", sep='\n')
    choix = input()

    if choix == "1":
        while 3:
            print("******************* THREE FISH *********************************************************")
            print("Chiffrer ? (press 1)","Déchiffrer ? (press 2)","Quitter ThreeFish ? (press 3)", sep='\n')
            choix_bis = input()
            if choix_bis == "1":
            if choix_bis == "2":
            if choix_bis == "3":
                break
    if choix == "2":
        CramerShoup.main_CramerShoup()
    if choix == "3":
        print("*****************************    HASHAGE   ******************************************************")
        Hash.main_hash()
    if choix == "4":
        break

print("*****************************************************************************************************************")

