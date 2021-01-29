# AweareHaptics

[![forthebadge](http://forthebadge.com/images/badges/built-with-love.svg)](http://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/built-by-developers.svg)](http://forthebadge.com) [![forthebadge](http://forthebadge.com/images/badges/powered-by-electricity.svg)](http://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/cc-nc-sa.svg)](http://forthebadge.com)


De nos jours, on compte parmis la population française plus de 207 000 aveugles et plus d’1 million de personnes souffrant de cécité visuelle. De plus, d’après l’OMS, le nombre de malvoyants pourrait trippler d’ici 2050. Actuellement, les outils d’aide développés pour ces personnes sont peu avancés technologiquement et nécessite souvent d’important coût d’achat. Nous avons donc décidé de développer un outil d’aide à l’orientation dans l’espace accessible à tous pour les personnes aveugles et malvoyantes.

**Aweare Haptics est une veste haptique open source permettant aux personnes aveugles et malvoyantes de s’orienter dans leur environnement.**


# Pour commencer

Entrez ici les instructions pour bien débuter avec votre projet...

### Pré-requis

Ce qu'il est requis pour commencer avec votre projet du point de vue du matériel

- Imprimante 3D
- Poste de soudure
- Poste de couture

# Démarrage

Notre veste sera composée de capteurs IR pour détecter la présence d’obstacle et de movuino pour transmettre l’information aux actuateurs présent sur la veste. L’emplacement des vibreurs a été déterminés par la réalisation d’une cartographie de sensibilité.

## Matériel

Pour chaque moteur vous aurez besoin de :

- faire faire un pcb néomotor : le fichier brd est dans le repo
- résistance 10Ω boitier 0805 : lien vers la [référence fabriquant : CRCW080510R0FKEA](https://fr.rs-online.com/web/p/resistances-cms/6790825/)
- résistance 100Ω boitier 0805 : lien vers la [référence fabriquant : CR0805-FX-1000ELF](https://fr.rs-online.com/web/p/resistances-cms/7408978/)
- résistance 442Ω boitier 0805 : lien vers la [référence fabriquant : ERA6AEB4420V](https://fr.rs-online.com/web/p/resistances-cms/7086023/)
- résistance 4KΩ boitier 0805 : lien vers la [référence fabriquant : CRCW08054K02FKEA](https://fr.rs-online.com/web/p/resistances-cms/6791471/)
- Condensateur type 104 : 10nF, boitier 0805 : lien vers la [référence fabriquant : CC0805KRX7R9BB103](https://fr.rs-online.com/web/p/condensateurs-ceramique-multicouches/4614013/)
- transitor npn simple boitier SOT-32 : lien vers la [référence fabriquant : MMBT3904LT1G](https://fr.rs-online.com/web/p/transistors-bipolaires-bjt/5450343/)
- moteur vibrant [Type Model NFP-P0716](https://nfpshop.com/product/7mm-vibration-motor-16mm-type-model-nfp-p0716-3v-12000rpm-7-3g-amplitude)

## Fabrication du pcb 

vous aurez besoin de commander ou bien de fabriquer des PCB, pour bien faire fonctionner les moteurs vibrant


 # Montage

 ## branchement 
 - brancher le GND de la movuino sur le GND du pcb
 - brancher le +5V de la movuino sur le +5V du pcb
 - brancher le +3V de la movuino sur le +3V du pcb
 - brancher la pin D9 de la movuino sur le DIN du pcb
 - brancher les deux fils sur moteur sur le bornes moteur du pcb. (le moteur n'est pas polarisé)

brancher ensuite :
 - le GND du pcb sur le GND du pcb suivant
 - le +5V de pcb sur le +5V du pcb suivant
 - le +3V de pcb sur le +3V du pcb suivant
 - la pin D9 de pcb sur le DIN du pcb suivant
 
 

 ## code 

téléverser le code source sue la movuino

la carte moovuino devient un serveur socket sur l'adresse 192.168.4.2
1 client max peut s'y connecter : ce nombre est modifiable dans le fichier ... : le define BN_CLIENT // TODO : dire ne nom du fichier  

le serveur ne fait que recevoir des messages des clients. le message doit etre formaté un string cntenant le numéo de l'actuateur à faire vibrer, ainsi qu'une intensité ayant une valeur comprise entre 0 et 3 

 ## souder les PCB



 ## monter..





# Auteurs

* [**Guicharnaud Léo**](https://github.com/Lightman31)
* [**Buot Adrien** ](https://github.com/Bubu781 )
* [**terre Mikhali** ](https://github.com/Mikhali)
* [**Sabatey Clara** ](https://github.com/clarasbty)
* [**Noiraux Coline** ](https://github.com/NoireauxColine)
* [**Beurotte Marine** ](https://github.com/mama98)


## Versions 
Liste des versions : [**Cliquer pour afficher les tags**](https://github.com/AweareHaptics/AweareHaptics/tags)



## Fabriqué avec

- [Arduino](https://www.arduino.cc/) - IDE
- [VScode](https://code.visualstudio.com/) + [PlatformIO](https://platformio.org/) - éditeur de texte et IDE
- [Fusion360](https://www.autodesk.fr/products/fusion-360/overview) - logiciel de modélisation 3D 
- [Eagle](https://www.autodesk.fr/products/eagle/overview) - logiciel de conception électronique

## License
Ce projet est sous licence ``exemple: WTFTPL`` - voir le fichier [LICENSE.md](LICENSE.md) pour plus d'informations

