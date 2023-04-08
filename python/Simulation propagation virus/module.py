import random
import time
from tkinter import *
menu = Tk()
MENUSIZE = (500, 500)
main_window_size = (500, 500)
WINDOWSTITLE = 'Propagation cellulaire'
menu.geometry(f'{MENUSIZE[0]}x{MENUSIZE[1]}')
menu.maxsize(MENUSIZE[0], MENUSIZE[1])
menu.minsize(MENUSIZE[0], MENUSIZE[1])
menu.title(WINDOWSTITLE)
#menu.iconbitmap('C:/Users/godme/Documents/Programmation/Python/Simulation propagation virus/coronavirus.ico')
menu.config(bg='#E5E5E5')

# Canvas Menu

menubar_canvas = Canvas(menu, width=MENUSIZE[0], height=55, bg='#1A5276', bd=0, highlightthicknes=0)
#img_menu_canvas = PhotoImage(file='C:/Users/godme/Documents/Programmation/Python/Simulation propagation virus/menu.png').subsample(15)
#menubar_canvas.create_image(32, 55 / 2, image=img_menu_canvas)
menubar_canvas.create_text(95, 55 / 2 - 1, text='Menu', fill='white', font=('Impact', 20))
menubar_canvas.place(x=0, y=40)

# Entrées

i = 140

cellules_saines = Entry(menu, bg='white', bd=1, font=('', 15), insertwidth=0, justify='center', relief='flat', width=15)
cellules_saines.place(x=(MENUSIZE[0] / 3) + 110, y=i)

facteur_r0 = Entry(menu, bg='white', bd=1, font=('', 15), insertwidth=0, justify='center', relief='flat', width=15)
facteur_r0.place(x=(MENUSIZE[0] / 3) + 110, y=i + 50)

taux_mortalite = Entry(menu, bg='white', bd=1, font=('', 15), insertwidth=0, justify='center', relief='flat', width=15)
taux_mortalite.place(x=(MENUSIZE[0] / 3) + 110, y=i + 100)

taille_monde = Entry(menu, bg='white', bd=1, font=('', 15), insertwidth=0, justify='center', relief='flat', width=15)
taille_monde.place(x=(MENUSIZE[0] / 3) + 110, y=i + 150)

facteur_immunite = Entry(menu, bg='white', bd=1, font=('', 15), insertwidth=0, justify='center', relief='flat', width=15)
facteur_immunite.place(x=(MENUSIZE[0] / 3) + 110, y=i + 200)

# Textes

cel_s_t = Label(menu, bg='#1A5276', width=19, height=1, font=('Impact', 13), relief='flat', text='Cellules saines',
                fg='white')
cel_s_t.place(x=MENUSIZE[0] / 3 - 104, y=i)

text_factor0 = Label(menu, bg='#1A5276', width=19, height=1, font=('Impact', 13), relief='flat', text='Facteur R0',
                     fg='white')
text_factor0.place(x=MENUSIZE[0] / 3 - 104, y=i + 50)

text_tauxmort = Label(menu, bg='#1A5276', width=19, height=1, font=('Impact', 13), relief='flat',
                      text='Taux de mortalité',
                      fg='white')
text_tauxmort.place(x=MENUSIZE[0] / 3 - 104, y=i + 100)

text_world = Label(menu, bg='#1A5276', width=19, height=1, font=('Impact', 13), relief='flat', text='Taille du monde',
                   fg='white')
text_world.place(x=MENUSIZE[0] / 3 - 104, y=i + 150)

text_facteurimm = Label(menu, bg='#1A5276', width=19, height=1, font=('Impact', 13), relief='flat',
                        text='Facteur immunité',
                        fg='white')
text_facteurimm.place(x=MENUSIZE[0] / 3 - 104, y=i + 200)


def openmainwindow():
    menu.withdraw()
    main = Tk()
    main.geometry(f'{main_window_size[0]}x{main_window_size[1]}')
    main.maxsize(main_window_size[0], main_window_size[1])
    main.minsize(main_window_size[0], main_window_size[1])
    main.title(WINDOWSTITLE)
    #main.iconbitmap('C:/Users/godme/Documents/Programmation/Python/Simulation propagation virus/coronavirus.ico')
    main.config(bg='#E5E5E5')

    # Fenêtre principale -> Menu
    def retour():
        # Suppression des valeurs dans les entrées
        cellules_saines.delete(0, END)
        facteur_r0.delete(0, END)
        taux_mortalite.delete(0, END)
        taille_monde.delete(0, END)
        facteur_immunite.delete(0, END)

        main.withdraw()
        menu.deiconify()

    # Barre de menu
    mainbar = Menu(main)
    retour_cascad = Menu(mainbar, tearoff=0)
    mainbar.add_cascade(label='Actions', menu=retour_cascad)
    retour_cascad.add_command(label='Menu Principal', command=retour)

    # Variables
    world_size = taille_monde.get()
    factor_r0 = facteur_r0.get()
    death_rate = taux_mortalite.get()
    healthy_cells = cellules_saines.get()
    immunity_factor = facteur_immunite.get()
    tags_squares = []
    largeur_ecart_carre_ligne = 0
    random_coords_healthy_cells = []
    dict_squares = {}
    red_square = []
    temp_list_g = []
    temp_list_w = []
    loop = 1
    cellules_jointes = []

    try:
        healthy_cells = int(healthy_cells)
        world_size = int(world_size)
        factor_r0 = int(world_size)
        death_rate = int(death_rate)
        immunity_factor = int(immunity_factor)
    except ValueError:
        print('Création du monde impossible')

    x_1, y_1, x_2, y_2, p = 0, 0, main_window_size[0] / world_size, main_window_size[1] / world_size, 1
    ecart_entre_lignes_h = 0
    ecart_entre_lignes_v = 0
    nbr_cases_vertes = 1
    ecart_entre_carre_h = main_window_size[0] / world_size
    ecart_entre_carre_v = main_window_size[1] / world_size

    # canvas principaux
    gride = Canvas(main, bd=0, bg='#E5E5E5', height=main_window_size[1], width=main_window_size[0])
    gride.pack()
    squares = Canvas(main, bd=0, bg='#E5E5E5', height=main_window_size[1], width=main_window_size[0])
    squares.place(x=0, y=0)

    time_d = time.time()
    # création des lignes
    for x in range(0, world_size + 1):
        gride.create_line(0, ecart_entre_lignes_h, main_window_size[0], ecart_entre_lignes_h)
        gride.create_line(ecart_entre_lignes_v, 0, ecart_entre_lignes_v, main_window_size[1])
        ecart_entre_lignes_v += main_window_size[0] / world_size
        ecart_entre_lignes_h += main_window_size[1] / world_size

    # création des carrés
    while loop <= main_window_size[0] / (main_window_size[0] / world_size) * main_window_size[1] / (main_window_size[1] / world_size):
        squares.create_rectangle(x_1 + largeur_ecart_carre_ligne, y_1 - largeur_ecart_carre_ligne,
                                 x_2 - largeur_ecart_carre_ligne, y_2 - largeur_ecart_carre_ligne, fill='white',
                                 tag=f'{loop}')
        tags_squares.append(squares.coords(loop))
        x_1 += main_window_size[0] / world_size
        x_2 += main_window_size[0] / world_size
        if x_2 >= main_window_size[0] + 5:
            x_1, y_1, x_2, y_2 = 0, main_window_size[1] / world_size * p + largeur_ecart_carre_ligne * 2, main_window_size[0] / world_size, main_window_size[1] / world_size * (p + 1)
            p += 1
        loop += 1

    # mise en place des carrés vert
    while nbr_cases_vertes <= healthy_cells:
        tags = squares.find_all()
        radm_tag = random.choice(tags)
        coords_random_tag = squares.coords(radm_tag)
        if coords_random_tag in random_coords_healthy_cells:
            coords_random_tag = squares.coords(radm_tag)
        else:
            squares.delete(radm_tag)
            random_coords_healthy_cells.append(coords_random_tag)
            tags_squares.remove(coords_random_tag)
            last = random_coords_healthy_cells[-1]
            squares.create_rectangle(last[0] + largeur_ecart_carre_ligne, last[1]-largeur_ecart_carre_ligne,
                                     last[2]-largeur_ecart_carre_ligne, last[3] - largeur_ecart_carre_ligne, fill='#4FD377',
                                     tag=f'{radm_tag}')
            nbr_cases_vertes += 1

    time_f = time.time()
    print('{:.2f}'.format(time_f-time_d))

    dict_squares['verte'] = random_coords_healthy_cells
    dict_squares['blanche'] = tags_squares

    def draw_virus(event):
        global sqr
        global temp
        closest = squares.find_closest(event.x, event.y)
        coords = squares.coords(closest)
        # si case est deja rouge
        if coords in red_square:
            if red_square[0] in temp_list_g:
                random_coords_healthy_cells.append(temp_list_g[0])
            if red_square[0] in temp_list_w:
                tags_squares.append(temp_list_w[0])
            temp_list_w.clear()
            temp_list_g.clear()
            if coords in random_coords_healthy_cells:
                color = '#4FD377'
            else:
                color = 'white'
            squares.create_rectangle(coords[0] + largeur_ecart_carre_ligne, coords[1] - largeur_ecart_carre_ligne, coords[2] - largeur_ecart_carre_ligne, coords[3] - largeur_ecart_carre_ligne, fill=color, tag=closest)
            red_square.remove(coords)
            cellules_jointes.clear()
        # sinon on met la case en rouge
        else:
            if len(red_square) > 0:
                print('Celulles infectées trop nombreuses !')
            else:
                red_square.append(squares.coords(closest))
                if red_square[0] in random_coords_healthy_cells:
                    random_coords_healthy_cells.remove(red_square[0])
                    temp_list_g.append(red_square[0])
                if red_square[0] in tags_squares:
                    tags_squares.remove(red_square[0])
                    temp_list_w.append(red_square[0])
                squares.delete(closest)
                squares.create_rectangle(coords[0] + largeur_ecart_carre_ligne, coords[1] - largeur_ecart_carre_ligne,
                                         coords[2] - largeur_ecart_carre_ligne, coords[3] - largeur_ecart_carre_ligne, fill='#FA2A2A',
                                         tag=closest)

                # ajouts des 8 cellules jointes dans une liste*
                red_square_var = red_square[0]
                # gauche
                j_0 = [red_square_var[0]-ecart_entre_carre_h, red_square_var[1], red_square_var[2]-ecart_entre_carre_h, red_square_var[3]]
                cellules_jointes.append(j_0)
                # droite
                j_1 = [red_square_var[0]+ecart_entre_carre_h, red_square_var[1], red_square_var[2]+ecart_entre_carre_h, red_square_var[3]]
                cellules_jointes.append(j_1)
                # bas
                j_2 = [red_square_var[0], red_square_var[1]+ecart_entre_carre_v, red_square_var[2], red_square_var[3]+ecart_entre_carre_v]
                cellules_jointes.append(j_2)
                # haut
                j_3 = [red_square_var[0], red_square_var[1]-ecart_entre_carre_v, red_square_var[2], red_square_var[3]-ecart_entre_carre_v]
                cellules_jointes.append(j_3)
                # supérieur gauche
                j_4 = [red_square_var[0]-ecart_entre_carre_h, red_square_var[1]-ecart_entre_carre_v, red_square_var[2]-ecart_entre_carre_h, red_square_var[3]-ecart_entre_carre_v]
                cellules_jointes.append(j_4)
                # supérieur droit
                j_5 = [red_square_var[0]+ecart_entre_carre_h, red_square_var[1]-ecart_entre_carre_v, red_square_var[2]+ecart_entre_carre_h, red_square_var[3]-ecart_entre_carre_v]
                cellules_jointes.append(j_5)
                # inférieur gauche
                j_6 = [red_square_var[0]-ecart_entre_carre_h, red_square_var[1]+ecart_entre_carre_v, red_square_var[2]-ecart_entre_carre_h, red_square_var[3]+ecart_entre_carre_v]
                cellules_jointes.append(j_6)
                # inférieur droit
                j_7 = [red_square_var[0]+ecart_entre_carre_h, red_square_var[1]+ecart_entre_carre_v, red_square_var[2]+ecart_entre_carre_h, red_square_var[3]+ecart_entre_carre_v]
                cellules_jointes.append(j_7)

                for cellule in cellules_jointes:
                    if cellule in dict_squares['verte']:
                        def temp():
                            squares.create_rectangle(sqr[0], sqr[1], sqr[2], sqr[3], fill='blue')
                            return
                    if sqr in dict_squares['blanche']:
                        def temp():
                            squares.create_rectangle(sqr[0], sqr[1], sqr[2], sqr[3], fill='black')
                            return
                    squares.after(500, temp)
                    print('ok')

        dict_squares['rouge'] = red_square

        for item, values in dict_squares.items():
            print(f'Il y a {len(values)} case(s) {item}(s)')
        print('\n')

    squares.bind_all('<Button-1>', draw_virus)

    main.config(menu=mainbar)
    main.mainloop()


def check():
    try:
        if int(taille_monde.get()) <= 2:
            print('La mise en monde est impossible\n')
        elif int(cellules_saines.get()) > main_window_size[0] / (main_window_size[0] / int(taille_monde.get())) * main_window_size[1] / (main_window_size[1] / int(taille_monde.get())):
            print('Le nombre de cellules saines est supérieur au nombre total de cellules !\n')
        else:
            openmainwindow()
    except ValueError:
        print('La mise en monde est impossible\n')


def check_1(event):
    check()


# Bouton start
start_button = Button(menu, bg='#1A5276', width=26, height=1, font=('Impact', 13),
                      relief='flat', text='Commencer la simulation', fg='white', cursor='X_cursor', command=check)
start_button.place(x=MENUSIZE[0] / 3 - 30, y=MENUSIZE[1] - 70)

menu.bind_all('<Return>', check_1)

menu.mainloop()
