
# Projet HMAE Nov2023 : 'LOVE BOX'


## Description du Projet

Le projet LOVE BOX est une application utilisant un écran OLED et un clavier pour envoyer et recevoir des emojis (smileys) via la communication sans fil à l'aide de la bibliothèque ESP-NOW sur des modules ESP32.

## Fichiers du Projet

### 1. `main.ino`

Le fichier principal du programme Arduino. Il initialise les composants, tels que l'écran OLED, le clavier, et la communication ESP-NOW. Il gère également le cycle principal du programme, y compris la réception et l'envoi d'emojis.

### 2. `Bitmaps.h`

Ce fichier d'en-tête contient les déclarations des tableaux d'images représentant différents smileys. Ces déclarations sont utilisées dans le programme principal pour afficher les emojis à l'écran.

### 3. `Bitmaps.cpp`

Le fichier source associé à `Bitmaps.h`. Il définit les tableaux d'images des smileys. Ces définitions sont incluses dans le programme principal pour utiliser les images.

### 4. `Keypad.h`

Un fichier d'en-tête qui définit une classe pour gérer le clavier matriciel. Cette classe est utilisée dans le programme principal (`main.ino`) pour détecter les touches pressées.


## Utilisation

1. Chargez le programme sur un module ESP32 à l'aide de l'IDE Arduino.
2. Changez la MAC address par celle de la carte de votre binome.
3. Utilisez le clavier pour sélectionner un emoji et appuyez sur la touche 'A' pour l'envoyer.
4. Appuyez sur la touche 'B' pour afficher un emoji reçu lorsque l'écran est allumé.
5. Vous pouvez eteindre l'ecran avec le bouton T (Select).
6. Meme l'ecran eteind, quand vous recevez un message l'ecran s'allume.
7. La touche S (Start) retourne au menu.


## Dépendances

- Bibliothèque Adafruit_GFX
- Bibliothèque Adafruit_SSD1306
- Bibliothèque Keypad
- Bibliothèque esp_now

## Auteur

Stanislas GADECEAU
Emma MOLERA

