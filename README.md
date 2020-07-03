# Smart_Fridge
Hackaton TIM

L'idea di base e' rappresentata da un dispositivo IoT provvisto di webcam che permetta il riconoscimento automatico tramite rete neurale di una serie di prodotti a cui sara' associata una data di scadenza. I dati popoleranno un database con notifica sul telefono dell'utente di un prodotto che abbia eventualmente superato la data di scadenza

La user experience deve essere al minimo impattante. L'utente deve solo presentare il prodotto alla camera ed attendere la conferma di riconoscimento dal dispositivo. In caso negativo sara' richiesto di scansionare il codice a barre. Un database di prodotti prevedera' la data di scadenza specifica (o generica in base alla categoria del prodotto....per esempio formaggio).

L'utente dovra' inoltre indicare se il prodotto e' in entrata od in uscita dal frigorifero in da effettuare il carico/scarico dalla tabella del db. Tale fase sara' gestita come speech recognition
