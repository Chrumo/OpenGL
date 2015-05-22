PV112-projekt-2.iterácia //veci ktore sa zmenili v druhej iteracii maju na zaciatku riadku 2.


Myšlienka:
2. V skriniach je nebezbečný plyn. Ak otvorite skrinu, plyn sa rozprchne do okolia a začnú svietit výstražné svetlá. Situáciu zachrániete jednoducho a to zatvorením skríň.

Odporúčaný scenár:
2. 1, Otvoriť a následne zatvoriť skrine.
2. 2, Vyskúšať si výpadok elektriny a svietiť si iba baterkou.
2. 3, Následne tieto 4 stavy(plyn zatvorený, plyn v miestnosti, výpadok elektriny, baterka) rôzne kombinovať.

Objekty:

Scéna je izba v ktorej sú umiestnené 3 skrine, 2 knižnice, stôl na ktorom je notebook a 2 lampicky, váza, hodiny a na strope žiarovka.



Animácie:

Hodiny sa posúvajú tak že minúta je jedna reálna sekunda, t.j. hodina je reálna minúta. Dá sa to prepnúť aby ukazovali reálny čas.
2. Výstražné zeleno-červené svetlá
2. Baterka, ako svetlo sa pohybuje s vami(mate ju v rukách)

Textury:
2. Hodiny som sa snažil otexturovať ale očividne nie sú dobre nastavené textúrovacie súradnice pre zvolený obrázok.
2. Na zemi je uložený zelený koberec zo vzorom. Steny vyzerajú ako reálne postavené(nie sú dokonale rovné vďaka textúre).
2. Skrine, stôl a knižnice sú otexturované rôznymi typmi dreva.
2. Váza je otexturovaná modrým vzorom.



Ovládanie:

w   - pohyb dopredu

s   - pohyb dozadu

a   - pohyb dolava

d   - pohyb doprava

myš - ovládanie pohladu kamery

r   - prestavenie hodín na reálny/fiktívny čas

e   - otvorenie/zatvorenie skrín ak ste dostatocne blízko(na obrazovke sa ukáže text "press E")

t   - vypína a zapína mód fullscreen

f   - zapína mód GL_FILL(objekty je možné vidiet vo vyplnenej podobe)

l   - zapína mód GL_LINE(objekty je možné vidiet v nevyplnenej podobe, t.j. iba úsecky jednotlivých polygonov z ktorých sa objekty skladajú)

m   - prepína medzi módom kedy je možné ovládat kurzor a kedy nie je možné ovládat kurzor


g   - 2. zapne/vypne baterku
h   - 2. výpadok elektriky a máte funkčnú iba baterku(prepína medzi týmito módmi

Osvetlenie:

Osvetlenie je bodové a vychádza zo žiarovky upevnenej na strope.


2. Pri otvorí skríň sa preprne na červeno-zelené výstražné svetlo a farba žiarovky sa upraví na zelenú.
2. Baterka.

Bonus:

Cez objekty nie je možné prechádzat.

Objekty sú ukladané do display listov.
2. Dymanické zapnutie/vypnutie hmly.
2. Výpadok elektriny a pohyb baterky.