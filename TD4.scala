package example

object TD4 {
    /*
    def addFunction(): (Int, Int) => Int = (x: Int, y: Int) => x + y

    def main(args: Array[String]): Unit = {
        val adding = addFunction()
        println(adding(1,2))
    }
    */

    def trouveAnagrammesDeRec(mot_ : String, motPartiel_ : String): scala.collection.mutable.Set[String] = {
        val anagrammes : scala.collection.mutable.Set[String] = scala.collection.mutable.Set()
        //println(motPartiel_ + " " + mot_)
        if (mot_.length > 0){
            (0 until mot_.length).toList.foreach(
                id => {
                    anagrammes addAll trouveAnagrammesDeRec(mot_.dropRight(mot_.length - id) + mot_.drop(id+1), (motPartiel_ + mot_(id)));
                }
            );
        }
        else {
            anagrammes addOne motPartiel_
        }
        return anagrammes
    }

    def trouveAnagrammesDe(mot_ : String): scala.collection.mutable.Set[String] = {
        return trouveAnagrammesDeRec(mot_, "")
    }

    def main(args: Array[String]): Unit = {
        var inputStr : String = scala.io.StdIn.readLine()
        val anagrammes = trouveAnagrammesDe(inputStr)
        anagrammes.foreach(str => println(str))
        println(anagrammes.size)
    }
}