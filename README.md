# 🍰 PF_API_2024

## 📖 Introduction 🇬🇧

This project has been developed as part of the study of **data structures** and **algorithms** in the **C programming language**.  
The main goal is to implement a program capable of solving a specific problem (as described in the giudelines) by applying efficient algorithmic strategies and suitable data structures.  

The program is designed to be evaluated through a series of **automated tests**, while strictly complying with given constraints on **execution time** and **memory usage**.  
The focus is therefore not only on the correctness of the solution but also on its efficiency and scalability.  

### 📌 Project guidelines

An industrial pastry shop wants to improve its order management system and has tasked you with developing software that simulates the pastry shop’s operations. The entire simulation takes place in discrete time. It is assumed that, after the execution of each command received as input, one time unit passes. The simulation starts at time 0. The simulation must take into account the following elements:

* The ingredients of the pastries, each identified by its name, consisting of a sequence of characters.
* The set of recipes offered by the pastry shop, also identified by a name. Each recipe uses different quantities of each required ingredient (specified as an integer number, in grams).
* The pastry shop’s ingredient warehouse, which stores all the ingredients used. The warehouse is restocked with new batches of ingredients, based on a schedule set by the supplier. Each batch is characterized by a quantity (always in grams) and an expiration date, indicated by the time instant after which the batch is considered expired.
* The pastry shop’s customers place orders for one or more pastries via an online platform or by phone. In either case, the pastry shop immediately begins preparing the ordered items. The advanced (and costly) machines used to prepare the pastries are so fast that it can be assumed that any number of pastries can be prepared within a single instant of the simulation. The necessary ingredients for each preparation are taken from the warehouse, always prioritizing batches with the closest expiration date.
If there are not enough ingredients available to fully prepare an order, it is put on hold. An arbitrary number of pending orders may exist. The pastry shop then continues preparing subsequent orders. At each restocking, the pastry shop evaluates whether the newly received ingredients allow it to prepare any pending orders. If so, they are prepared at that same time instant. Pending orders are processed in chronological order of arrival.
* Periodically, the courier arrives at the pastry shop to collect the prepared orders. Upon the courier’s arrival, the orders to be loaded are selected in chronological order of arrival. The process stops as soon as an order is encountered that exceeds the remaining capacity (in grams) of the delivery van. It is assumed that the weight of each prepared pastry is equal to the sum of the quantities in grams of each ingredient. Each order is always loaded in its entirety. Once the orders are chosen, the pastry shop proceeds to load them in descending order of weight. If two orders have the same weight, they are loaded in chronological order of arrival.

It is assumed that all quantities are integers greater than zero, regardless of the unit of measurement. Names, whether of ingredients or recipes, are defined over the alphabet {a, ..., z, A, ..., Z, _} and can be up to 255 characters long. The simulation ends after reading the last command.
The input text file begins with a line containing two integers: the courier’s frequency and its capacity. This is followed by a sequence of commands, one per line, in the following format. All positive or zero integer values are encodable in 32 bits.

* ___add_recipe ⟨recipe_name⟩ ⟨ingredient_name⟩ ⟨quantity⟩ ...___  
➡️ Example: add_recipe great_aunt_meringues sugar 100 egg_whites 100  
➡️ Adds a recipe to the catalog. The number of pairs (⟨ingredient_name⟩ ⟨quantity⟩) is arbitrary. If a recipe with the same name already exists, it is ignored.  
➡️ Expected output: _added_ or _ignored_.  
* ___remove_recipe ⟨recipe_name⟩___  
➡️ Example: remove_recipe cream_cannoli  
➡️ Removes a recipe from the catalog. Has no effect if the recipe is not present, or if there are pending orders related to it that have not yet been shipped.  
➡️ Expected output: _removed_, _pending_orders_, or _not_found_.  
* ___restock ⟨ingredient_name⟩ ⟨quantity⟩ ⟨expiration⟩ ...___  
➡️ Example: restock sugar 200 150 flour 1000 220  
➡️ The pastry shop is restocked with a set of batches, one per ingredient. The number of batches is arbitrary.  
➡️ Expected output: _restocked_.  
* ___order ⟨recipe_name⟩ ⟨number_of_items⟩___  
➡️ Example: order paradise_cake 36  
➡️ Places an order of ⟨number_of_items⟩ pastries with recipe ⟨recipe_name⟩.  
➡️ Expected output: _accepted_ or _rejected_ if no recipe with the given name exists.  

In addition to the outputs listed above, the program prints the orders loaded into the courier’s van as a sequence of triples: ___⟨order_arrival_time⟩ ⟨recipe_name⟩ ⟨number_of_items⟩___
one per line, in loading order. For a courier with frequency _n_, the output is generated before processing commands at time _kn_ with _k_ ∈ 1, 2, .... If the van is empty, the message _empty van_ is printed.

---

## 📖 Introduzione 🇮🇹

Questo progetto è stato sviluppato nell’ambito dello studio delle **strutture dati** e degli **algoritmi** in linguaggio **C**.   
L’obiettivo principale è implementare un programma capace di risolvere un problema specifico (riportato nella consegna) utilizzando strategie algoritmiche efficienti e strutture dati adeguate.  

Il programma è stato progettato per essere valutato attraverso una serie di **test automatici**, rispettando vincoli stringenti in termini di **tempo di esecuzione** e **utilizzo della memoria**. L’enfasi è posta quindi non solo sulla correttezza della soluzione, ma anche sulla sua efficienza e scalabilità.

### 📌 Traccia del progetto

Una pasticceria industriale vuole migliorare il proprio sistema di gestione degli ordini, e vi incarica di sviluppare un software che simuli il funzionamento della pasticceria. L’intera simulazione avviene a tempo discreto. Si assuma che, a valle dell’esecuzione di ogni comando ricevuto in ingresso, trascorra un istante di tempo. La simulazione ha inizio al tempo 0. Nella simulazione si dovranno considerare i seguenti elementi:

* Gli ingredienti dei dolci, ognuno identificato dal suo nome, costituito da una sequenza di caratteri.
* L’insieme delle ricette offerte dalla pasticceria, identificate anch’esse da un nome. Ogni ricetta utilizza diverse quantità di ciascun ingrediente necessario (indicate da un numero intero, in grammi).
* Il magazzino degli ingredienti della pasticceria, che stocca ogni ingrediente utilizzato. Il magazzino viene rifornito da nuovi lotti di ingredienti, in base a una pianificazione stabilita dal fornitore. Ogni lotto è caratterizzato da una quantità (sempre in grammi) e da una data di scadenza, indicata dal numero dell’istante di tempo a partire dal quale il lotto è scaduto.
* I clienti della pasticceria effettuano ordini di uno o più dolci tramite una piattaforma online o per telefono. In ogni caso, la pasticceria procede subito a preparare i dolciumi ordinati. Gli avanzati (e costosi) macchinari che preparano i dolci sono così veloci che si può assumere che la preparazione di un numero arbitrario di dolci avvenga in un singolo istante della simulazione. Gli ingredienti necessari per ogni preparazione vengono prelevati dal magazzino privilegiando sempre i lotti con la scadenza più prossima. Se non sono disponibili ingredienti a sufficienza da consentire la preparazione per intero di un ordine, esso viene messo in attesa. È possibile avere un numero arbitrario di ordini in attesa. La pasticceria procede a preparare eventuali ordini successivi. Ad ogni rifornimento, la pasticceria valuta se è possibile, con gli ingredienti ricevuti, preparare ordini attualmente in attesa. Se questo è il caso, li prepara nello stesso istante di tempo. Gli ordini in attesa vengono smaltiti in ordine cronologico di arrivo dell’ordine.
* Periodicamente, il corriere si reca dalla pasticceria a ritirare gli ordini pronti. All’arrivo del corriere, gli ordini da caricare vengono scelti in ordine cronologico di arrivo. Il processo si ferma appena viene incontrato un ordine che supera la capienza rimasta (in grammi) sul camioncino. Si assuma che il peso di ogni dolce preparato sia uguale alla somma delle quantità in grammi di ciascun ingrediente. Ogni ordine viene sempre caricato nella sua interezza. Scelti gli ordini, la pasticceria procede a caricarli in ordine di peso decrescente. A parità di peso, gli ordini vanno caricati in ordine cronologico di arrivo.

Si assuma che tutte le quantità siano intere e maggiori di zero, indipendentemente dall’unità di misura. I nomi, siano essi di ingredienti o ricette, sono definiti sull’alfabeto {a, ..., z, A, ..., Z, _} e sono lunghi fino a 255 caratteri. La simulazione termina in seguito alla lettura dell’ultimo comando. Il file testuale in ingresso inizia con una riga contenente due interi: la periodicità del corriere e la sua capienza. Seguono una sequenza di comandi, uno per riga, con il seguente formato. Tutti i valori interi positivi o nulli sono codificabili in 32 bit.

* ___aggiungi_ricetta ⟨nome_ricetta⟩ ⟨nome_ingrediente⟩ ⟨quantità⟩ ...___  
➡️ Esempio: aggiungi_ricetta meringhe_della_prozia zucchero 100 albumi 100  
➡️ Aggiunge una ricetta al catalogo. Il numero di coppie (⟨nome_ingrediente⟩ ⟨quantità⟩) è arbitrario. Se una ricetta con lo stesso nome è già presente, viene ignorato.  
➡️ Stampa attesa come risposta: _aggiunta_ oppure _ignorato_.  
* ___rimuovi_ricetta ⟨nome_ricetta⟩___  
➡️ Esempio: rimuovi_ricetta cannoncini  
➡️ Rimuove una ricetta dal catalogo. Non ha effetto se la ricetta non è presente, oppure ci sono ordini relativi ad essa non ancora spediti.  
➡️ Stampa attesa come risposta: _rimossa_, _ordini in sospeso_ oppure _non presente_.  
* ___rifornimento ⟨nome_ingrediente⟩ ⟨quantità⟩ ⟨scadenza⟩ ...___  
➡️ Esempio: rifornimento zucchero 200 150 farina 1000 220  
➡️ La pasticceria viene rifornita di un insieme di lotti, uno per ingrediente. Il numero di lotti è arbitrario.  
➡️ Stampa attesa come risposta: _rifornito_.  
* ___ordine ⟨nome_ricetta⟩ ⟨numero_elementi_ordinati⟩___  
➡️ Esempio: ordine torta_paradiso 36  
➡️ Effettua un ordine di ⟨numero_elementi_ordinati⟩ dolci con ricetta ⟨nome_ricetta⟩.  
➡️ Stampa attesa come risposta: _accettato_ oppure _rifiutato_ se non esiste nessuna ricetta col nome specificato.

In aggiunta alle stampe sopraelencate, il programma stampa gli ordini contenuti nel camioncino del corriere come una sequenza di triple ___⟨istante_di_arrivo_ordine⟩ ⟨nome_ricetta⟩ ⟨numero_elementi_ordinati⟩___, una per rigo, in ordine di caricamento. Dato un corriere di periodicità _n_, la stampa è effettuata prima di gestire i comandi al tempo _kn_ con _k_ ∈ 1, 2, . . .. Se il camioncino è vuoto, viene stampato il messaggio _camioncino vuoto_.
