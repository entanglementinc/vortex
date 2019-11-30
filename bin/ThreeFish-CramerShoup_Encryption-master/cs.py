 # encoding=utf-8
import sys
import CramerShoup
import Hash
import codecs



while 1:
    print('\n')
    print("***************************       MENU PRINCIPAL        ****************************************************************")
    print("Souhaitez vous:", "ThreeFish (Press 1) ", "Cramer-Shoup (Press 2)")
    
    choix = input()

    
    if choix == "2":
        CramerShoup.main_CramerShoup()
    if choix == "3":
     
        Hash.main_hash()
    if choix == "4":
        break



