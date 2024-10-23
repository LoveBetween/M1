object TD4ter {
    def main(args: Array[String]): Unit = {
        //1
        println("question1")
        //2
        val l : List[String]= List[String]("test1", "test2", "a")
        l.foreach(a => print(a + ", "))
        println()
        //3
        println(l(2))
        //4
        l.map((elt:String) => "("+elt+")")
        l.foreach(a => print(a + ", "))
        println()
        // l n'est pas modifie car map retourne une nouvelle collection 
        // et val declare qqchose d'immuable
        l.map("("+ _ +")").foreach(a => print(a + " "))
        println()
        // on itere sur la nouvelle collection cree par map pour afficher
        
        //5, 6
        val l1 : List[Int] = List[Int](1, 2, 5)
        val s1 : String = "ma liste= " ++ l1.mkString(" puis ") ++ " et voila"
        println(s1)

        //7
        val lpair : List[Int] = l1.filter(_%2 == 0)
        println(lpair.mkString(" , "))

        //8
        val c : Tuple2[Int, Int] = Tuple2[Int, Int](4,8)
        println(c)
        println(c._1)
        println(c._2)
        //9
        val c2 = (4,8)
        println(c2)

        //10
        val lpairimpair : Tuple2[List[Int], List[Int]] = l1.partition(_%2 == 0)
        println(lpairimpair._1.mkString(" , ")) 
        println(lpairimpair._2.mkString(" , ")) 

        //11
        l1.permutations.foreach(println)
        // Le type obtenu par permutations de List[Int] est un Iterator[List[Int]]

        //12
        val l2 : List[Int] = List[Int](1,2,3,8,9)
        println()
        l2.permutations.foreach(a => println("List(" ++ a.mkString(", ") ++ ")"))

        //13
        l2.permutations.foreach(a => println(a.mkString("-")))

        //14
        val cc : String = "abcd"
        cc.permutations.foreach(println)

        //15
        println()
        cc.permutations.toSet.foreach(println)

        //16
        // c'est bien note

        //17
        println(l2.filter(_%2==0).mkString(", "))

        //18
        // C'est bien noté, je ne ferais plus de foreach comme à la question 2

        //19
        val l3 : List[String] = List[String]("merde", "avion", "eau", "con", "train")
        val grosmots : List[String] = List[String]("merde", "con", "boudin")

        println(l3.map(a => if (grosmots.contains(a)) "***" else a).mkString(", "))

        //20
        println(l3.filter(! grosmots.contains(_)).mkString(", "))

        //21
        println(cc.reverse)
        // ça inverse l'ordre des caracteres

        //22
        // Une chaine de caracteres est une collection dont les caracteres sont les elements
        // reverse inverse l'ordre des éléments

        //23
        println(l3.reverse.permutations.toSet.equals(l3.permutations.toSet))

        //24
        val paloupas : List[String] = List[String]("rotor", "Hannah", "chien", "tout", "Bob")

        println(paloupas.filter(a=> a.toLowerCase().equals(a.toLowerCase().reverse)).mkString(", "))

        //25
        val cesar : String = "Tu l'as trop écrasé, César, ce Port-Salut"
        println(cesar.toLowerCase().equals(cesar.toLowerCase().reverse))
        // ce n'est pas un palindrome si on considere les accents et la ponctuations
        println(cesar.replaceAll("é", "e").filter(a => a.isLetterOrDigit).toLowerCase() == cesar.replaceAll("é", "e").filter(a => a.isLetterOrDigit).toLowerCase().reverse)
        // en renplaçant les accents et en enlevant toute la ponctutaion et les espaces, ont vérifie que c'est un palindrome
    }
}