//-- Eötvös Loránd Tudományegyetem; 2020/21 tanév, II. félév, Objektum Elvű Programozás 3. beadandó
//-- Kiss Barnabás
//-- 2021.07.02.

A doc/pdf dokumentáció a tantárgyi elvárásoknak megfelelően készült el, amely így tartalmazza a feladat leírását,
specifikációját, algoritmusát és a megoldás tervét.

A feladat leírása alább is megtekinthető.


***************************

          Feladat

***************************


A turisták látogatása bevételt hoz egy városnak, de kis mértékben rontja is a város állapotát. Egy város, ami jó állapotban van, vonzza a turistákat.
Egy rossz állapotú város taszítja az odalátogatni készülőket.

Egy turista látogatása átlagosan 100.000 Ft bevételt hoz a városnak. Ha a város bevétele egy évben meghaladja az egy milliárd forintot,
az egy milliárdon felüli részt a város javítására és szépítésére fordítják, hogy több látogató érkezzen a következő évben. A város állapota 1 és 100 pont között mozog
(1 alá és 100 fölé sose megy, mert az állam elkölti a fölösleget és besegít, ha már nagyon vészes a helyzet). 1 és 33 közt számít lepusztultnak, 34 és 67 között átlagosnak és 67 fölött jó állapotúnak.
Minden évben egy milliárd forint bevétel fölött minden húszmillió forint hoz egy pont állapotjavulást a városnak.

A turisták 3 fajtába sorolhatók: a japánok rendet raknak maguk után, így ők nem rontják a város állapotát. A modern országokból érkező turisták kevésbé ügyelnek a környezetükre:
100-asával rontanak egy-egy pontot a város állapotán. A harmadik csoportba sorolható turisták azon országok képviselői, ahol a szemetelés kulturális szokásnak tekinthető,
ők 50-esével rontanak egy-egy pontot a város állapotán.

Ha a város jó állapotban van, abban az évben 20%-kal több japánt és 30%-kal több modernt vonz, mint ahány tervezte, hogy ellátogat oda.
Átlagos állapotban 10%-kal több modernt és 10%-kal több harmadik típusú turistát vonz. Lepusztult állapot esetén a japánok egyáltalán nem jönnek, a többiek pedig annyian, amennyien tervezték.

Adjuk meg, hogy a fájlban jelölt évek letelte után milyen a város állapota! Körönként mutassuk meg az érkezett turisták számát
(hány tervezett és hány jött) kategóriák szerint, az éves bevételt és a város felújítás előtti állapotát (szám és kategória)!

A program egy szövegfájlból olvassa be az adatokat! Az első sorban a város kezdeti állapota szerepel. A második sor jelöli a szimulált évek számát.
A következő sorok tartalmazzák, hogy az egyes években hány turista tervezte, hogy eljön a városba: minden sor 3 darabszámot tartalmaz (japánok, modernek, többiek).
A program kérje be a fájl nevét, majd jelenítse is meg a tartalmát. (Feltehetjük, hogy a fájl formátuma helyes.) Egy lehetséges bemenet:

50
3
1000 4000 6000
2000 3000 8000
6500 5000 3000

*---------------------------------------------------*
      Egyéb elvárások a programmal kapcsolatban
*---------------------------------------------------*

Csak azt a funkcionálisan működő (a kitűzött feladatot megoldó), felhasználó barát, bolond biztos input-output felületű alkalmazást fogadjuk el,
amelyhez a megadott feltételeket kielégítő terv-dokumentáció tartozik, és amelynek kódja a tervnek megfelel, és automatikus tesztkörnyezettel rendelkezik.
A feladatok megoldásához több olyan osztályt kell használni, amelyek egy közös ősosztályból származnak és felüldefiniálják az ősosztály virtuális metódusait.
Ezen osztályok objektumait egy gyűjteménybe kell elhelyezni, majd ezt a gyűjteményt kell bejárni, a benne levő objektumok megfelelő metódusait meghívni.
Ez a bejárás a futásidejű polimorfizmusra támaszkodik. Használjon legalább két tervezési mintát is.
A gyűjtemények bejárását továbbra is a tanult programozási tételek alapján végezze.
A tesztkörnyezet biztosítson egységenkénti (osztály, metódus) tesztelési eseteket is a végfelhasználói teszteseteken kívül.