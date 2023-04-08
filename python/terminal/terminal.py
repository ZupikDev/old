import os
import time as t
import random
from tkinter import *
from math import pi
# par zupik le 25/01/21



def main():
    name = "Default"
    while True:
        terminal = input(f"[{name}]> command ; [help] ; [Credits] ; [Terminal_name] ")
        if terminal == 'help':
            terminal = input(f"[{name}]> Vous trouvez tous les projets avec les commandes suivantes "
                             f": 'aires' ; 'moyenne' ; 'calculette' ; 'loto' ")
            continue
        elif terminal == 'Credits':
            terminal = input(f"[{name}]> Penser et développer par Benjamin. ")
            continue
        elif terminal == "Terminal_name":
            terminal = input(f"[{name}]> Nom du terminal : ")
            name = terminal
            continue
        elif terminal == 'aires':
            window = Tk()
            window.minsize(750, 200)
            window.maxsize(750, 200)
            window.title("Aires")
            window.config(bg="#FF5E4D")
       
            # Menu
       
            menubar = Menu(window)
            window.config(menu=menubar)
       
            menufichier = Menu(menubar, tearoff=0)
            menubar.add_cascade(label="Actions", menu=menufichier)
       
            # Carr�
       
            frame_square = Frame(window, bg="#FF5E4D")
       
            square_text = "Entrer côté carré (en m)"
            square_label = Label(frame_square, text=square_text, bg="#FF5E4D", font=("", 12), fg="#C0C0C0")
            square_label.pack()
       
            formule = Entry(frame_square, font=("", 10), bg="#FF5E4D")
            formule.pack(ipady=7, padx=5)
       
            name_square = Label(window, text="Carré", bg="#FF5E4D", font=("", 18), fg="#C0C0C0")
            name_square.place(x=50, y=165)
       
            def result_square():
                try:
                    volume_square = formule.get()
                    formule.delete(0, END)
                    volume_final = int(volume_square) * int(volume_square)
                    volume_final = str(volume_final), "m²"
                    formule.insert(0, volume_final)
                except ValueError:
                    pass
       
            def clear():
                formule.delete(0, END)
       
            button_square = Button(frame_square, text="Calculer", font=("", 13), bg="#FF5E4D", fg="#C0C0C0",
                                   command=result_square)
            button_square.pack(pady=5)
       
            button_clear_square = Button(frame_square, text="Nettoyer", font=("", 13), bg="#FF5E4D", fg="#C0C0C0",
                                         command=clear)
            button_clear_square.pack(pady=5)
       
            frame_square.grid(sticky=W, pady=22)
       
            # Rectangle
       
            frame_rectangle = Frame(window, bg="#FF5E4D")
       
            rectangle_text = "Longueur"
            rectangle_label = Label(frame_rectangle, text=rectangle_text, bg="#FF5E4D", font=("", 12), fg="#C0C0C0")
            rectangle_label.grid(column=1, pady=20, row=1, padx=60)
       
            name_rectangle = Label(window, text="Rectangle", bg="#FF5E4D", font=("", 15), fg="#C0C0C0")
            name_rectangle.place(x=256, y=165)
       
            rectangle_label_width = Label(window, text="Largeur", bg="#FF5E4D", font=("", 12), fg="#C0C0C0")
            rectangle_label_width.place(x=315, y=21)
       
            entry_height_rectangle = Entry(window, font=("", 13), bg="#FF5E4D", width=7)
            entry_height_rectangle.place(x=230, y=50)
       
            entry_weight_rectangle = Entry(window, font=("", 13), bg="#FF5E4D", width=7)
            entry_weight_rectangle.place(x=315, y=50)
       
            def rectangle_final():
                try:
                    width_final_rectangle = entry_height_rectangle.get()
                    height_final_rectangle = entry_height_rectangle.get()
                    entry_weight_rectangle.delete(0, END)
                    entry_height_rectangle.delete(0, END)
                    entry_result_rectangle.delete(0, END)
                    volume_final_rectangle = int(width_final_rectangle) * int(height_final_rectangle)
                    volume_final_rectangle = str(volume_final_rectangle), "m�"
                    entry_result_rectangle.insert(0, volume_final_rectangle)
                except ValueError:
                    entry_weight_rectangle.delete(0, END)
                    entry_height_rectangle.delete(0, END)
       
            button_rectangle = Button(window, text="Calculer", font=("", 13), bg="#FF5E4D", fg="#C0C0C0",
                                      command=rectangle_final)
            button_rectangle.place(x=228, y=80)
       
            entry_result_rectangle = Entry(window, font=("", 13), bg="#FF5E4D", width=9)
            entry_result_rectangle.place(x=262, y=120)
       
            def clear_rectangle():
                entry_weight_rectangle.delete(0, END)
                entry_height_rectangle.delete(0, END)
                entry_result_rectangle.delete(0, END)
       
            button_rectangle_clear = Button(window, text="Nettoyer",
                                            font=("", 13), bg="#FF5E4D", fg="#C0C0C0", command=clear_rectangle)
       
            button_rectangle_clear.place(x=310, y=80)
       
            frame_rectangle.grid(column=2, row=0, sticky=N)
       
            # Triangle
       
            triangle_label = Label(window, text="base", bg="#FF5E4D", font=("", 12), fg="#C0C0C0")
            triangle_label.place(x=505, y=21)
       
            name_triangle = Label(window, text="Triangle", bg="#FF5E4D", font=("", 15), fg="#C0C0C0")
            name_triangle.place(x=455, y=165)
       
            triangle_label_height = Label(window, text="hauteur", bg="#FF5E4D", font=("", 12), fg="#C0C0C0")
            triangle_label_height.place(x=425, y=21)
       
            entry_height_triangle = Entry(window, font=("", 13), bg="#FF5E4D", width=7)
            entry_height_triangle.place(x=420, y=50)
       
            entry_base_triangle = Entry(window, font=("", 13), bg="#FF5E4D", width=7)
            entry_base_triangle.place(x=495, y=50)
       
            def clean():
                entry_base_triangle.delete(0, END)
                entry_result_triangle.delete(0, END)
                entry_height_triangle.delete(0, END)
       
            def final_triangle():
                try:
                    final_base_triangle = entry_base_triangle.get()
                    final_height_triangle = entry_height_triangle.get()
                    clean()
                    final_result_triangle = (int(final_height_triangle) * int(final_base_triangle)) / 2
                    final_result_triangle = str(final_result_triangle), "m²"
                    entry_result_triangle.insert(0, final_result_triangle)
                except ValueError:
                    clean()
       
            button_triangle = Button(window, text="Calculer", font=("", 13), bg="#FF5E4D", fg="#C0C0C0", command=final_triangle)
            button_triangle.place(x=415, y=80)
       
            button_triangle = Button(window, text="Nettoyer", font=("", 13), bg="#FF5E4D", fg="#C0C0C0", command=clean)
       
            button_triangle.place(x=495, y=80)
       
            entry_result_triangle = Entry(window, font=("", 13), bg="#FF5E4D", width=9)
            entry_result_triangle.place(x=450, y=120)
       
            # Disque
       
            disk_label_rayon = Label(window, text="Rayon", bg="#FF5E4D", font=("", 12), fg="#C0C0C0")
            disk_label_rayon.place(x=610, y=21)
       
            name_disk = Label(window, text="Disque", bg="#FF5E4D", font=("", 15), fg="#C0C0C0")
            name_disk.place(x=605, y=165)
       
            entry_rayon_disk = Entry(window, font=("", 13), bg="#FF5E4D", width=9)
            entry_rayon_disk.place(x=593, y=50)
       
            def clean_disk():
                entry_rayon_disk.delete(0, END)
       
            def calcul_disk():
                try:
                    final_rayon_disk = entry_rayon_disk.get()
                    result_disk = (int(final_rayon_disk) * int(final_rayon_disk)) * pi
                    result_disk = round(result_disk, 4)
                    result_disk = str(result_disk), "m²"
                    clean_disk()
                    entry_rayon_disk.insert(0, result_disk)
                except ValueError:
                    clean_disk()
       
            button_disk = Button(window, text="Calculer", font=("", 13), bg="#FF5E4D", fg="#C0C0C0", command=calcul_disk)
            button_disk.place(x=600, y=80)
       
            button_disk_nettoyer = Button(window, text="Nettoyer", font=("", 13), bg="#FF5E4D", fg="#C0C0C0",
                                          command=clean_disk)
       
            button_disk_nettoyer.place(x=600, y=120)
       
            def clear_all():
                clean()
                clear()
                clear_rectangle()
                clean_disk()
       
            def result_all():
                final_triangle()
                rectangle_final()
                result_square()
                calcul_disk()
       
            def window_two():
                fnt = Tk()
                fnt.minsize(750, 200)
                fnt.maxsize(750, 200)
                fnt.title("Volumes")
                fnt.iconbitmap("formula.Ico")
                fnt.config(bg="#FF5E4D")
                menubar_two = Menu(fnt)
                fnt.config(menu=menubar_two)
                menu_deux = Menu(menubar_two, tearoff=0)
       
                def win_to_second():
                    fnt.withdraw()
                    window.deiconify()
       
                menubar_two.add_cascade(label="Actions", menu=menu_deux)
                menu_deux.add_command(label="Aires", command=win_to_second)
       
                flemme = Label(fnt, text="FLEMME DE CONTINUER POUR AU FINAL NE JAMAIS M'EN SERVIR", font=("", 16), bg="#FF5E4D")
                flemme.pack()
       
            def clear_window():
                window.withdraw()
                window_two()
       
            menufichier.add_command(label="Volumes", command=clear_window)
            menufichier.add_command(label="Réinitialiser", command=clear_all)
            menufichier.add_command(label="Tout calculer", command=result_all)
       
            window.config(menu=menubar)
            window.mainloop()
           
        elif terminal == 'moyenne':
            def m():
                try:
                    terminal = input(f"[{name}]> Entrer les moyennes (format : m;m,d) : ")
           
                    liste = []
                    var_m = 0
                    liste_f = []
               
                    try:
                        for a in terminal.split(";"):
                            try:
                                liste.append(a.replace(",", "."))
                            except ValueError:
                                liste.append(a)
                                continue
                    except ValueError:
                        print(f"[{name}]> Une erreur est surevenue.")
               
                    total_moyenne = len(liste)
                    if total_moyenne <= 1:
                        b = "".join(liste)
                        print(f"[{name}]> Il est impossible de faire une moyenne générale avec un seule moyenne ('{b}'/20)\n")
                        t.sleep(2)
                        m()
               
                    print("[%s]> %s moyennes rentrées. (%s -> %s)" % (name, total_moyenne, liste[0], liste[-1]))
                    t.sleep(0.5)
               
                    for n in liste:
                        liste_f.append(float(n))
               
                    del liste
               
                    for i in liste_f:
                        var_m += i
               
                    result = var_m / len(liste_f)
                    result = round(result, 2)
                    print("[{}]> Votre moyenne est de : {}/20 points.".format(name, result))
                    t.sleep(1)
               
                    i = input(f"[{name}]> Continuer ? N/O : ")
               
                    if i == "N" or i == "n":
                        pass
                    else:
                        m()
                except:
                    m()
            m()
            continue
        elif terminal == 'calculette':
            def clear_file():
                with open("text.txt", "w") as t:
                    t.write("")
                    t.close()
   
            window = Tk()
            window.geometry("500x190")
            window.title("Calculator")
            window.config(bg="#B94127")
            window.iconbitmap("calculator.ico")
            window.minsize(500, 190)
            window.maxsize(500, 190)
            # Titre
            title = Label(window, bg="#B94127", font=("", 40), text="Calculator", fg="#BCB8B8")
            title.pack(side=TOP)
            # Entrer une table
            text_table = Label(window, bg="#B94127", font=("", 20), text="Entrez une table :", fg="#BCB8B8")
            text_table.place(x=20, y=100)
            # Entrer un multiplicateur
            text_multipli = Label(window, bg="#B94127", font=("", 17), text="Entrez un multiplicateur max :", fg="#BCB8B8")
            text_multipli.place(x=20, y=150)
            # entr�e entrer une table
            entry_1 = Entry(window, bg="#B94127", font=("", 15), width=15)
            entry_1.place(x=245, y=105)
            # Multiplicateur max
            entry_2 = Entry(window, bg="#B94127", font=("", 15), width=15)
            entry_2.place(x=325, y=155)
           
            def clear_entry(event):
                entry_1.delete(0, END)
                entry_2.delete(0, END)
           
            def calculator(event):
                a, b, = int(entry_1.get()), int(entry_2.get())
                c = 1
                with open("text.txt", "a") as file_text:
                    while c <= b:
                        file_text.write(f"{a} x {c} = {a*c}\n")
                        c += 1
                    file_text.write("\n-----------------------------------\n")
                    file_text.close()
                entry_1.delete(0, END)
                entry_2.delete(0, END)
           
            # Menu
            menubar = Menu(window)
            menufichier = Menu(menubar, tearoff=0)
            menubar.add_cascade(label="Actions", menu=menufichier)
           
            menufichier.add_command(label="Supprimer contenu fichier", command=clear_file)
            menufichier.add_command(label="Supprimer variables", command=clear_entry)
           
            entry_2.bind("<Return>", calculator)
           
            window.config(menu=menubar)
            window.mainloop()
        elif terminal == 'loto':
            # Euromillion
           
            liste_1_50 = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
                          30, 31, 32, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 45, 46, 47, 48, 49, 50]
            liste_lucky_star = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
           
            liste_final = []
            a = 0
            while a <= 5:
                liste_final.append(random.choice(liste_1_50))
                a += 1
            i = 1
            lucky_liste = []
            while i <= 2:
                lucky_liste.append(random.choice(liste_lucky_star))
                i += 1
           
            print(f"[{name}]> Numéros Euromilions : \n[{name}]> 5 Numéros : {liste_final[0]}, {liste_final[1]}, {liste_final[2]}, {liste_final[3]} et "
                  f"{liste_final[4]} !\n[{name}]> Numéros chances : {lucky_liste[0]}, {lucky_liste[1]}\n")
           
            # Loto
           
            liste_loto = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
                          30, 31, 32, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 45, 46, 47, 48, 49]
            liste_lucky_loto = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
            list_final_loto = []
            liste_loto_l = []
           
            var = 0
           
            while var <= 5:
                list_final_loto.append(random.choice(liste_loto))
                var += 1
           
            liste_loto_l.append(random.choice(liste_lucky_loto))
           
           
            print(f"[{name}]> Loto :\n[{name}]> 5 Numéros : {list_final_loto[0]}, {list_final_loto[1]}, {list_final_loto[3]}, {list_final_loto[4]}"
                  f" et {list_final_loto[5]} !\n[{name}]> Un numéro chance : {liste_loto_l[0]}")
            continue
        else:
            terminal = input(f"[{name}]> La commande n'existe pas !")
            continue
    os.system("PAUSE")


if __name__ == "__main__":
    main()

os.system("PAUSE")
