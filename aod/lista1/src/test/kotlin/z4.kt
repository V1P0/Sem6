class z4 {
    @org.junit.jupiter.api.Test
    fun test1(){
        var tests = mutableListOf<String>()
        for(i in 1..6){
            tests.add("src/resources/4/d4a-$i.txt")
        }
        for(i in 1..6){
            tests.add("src/resources/4/u4a-$i.txt")
        }
        for(test in tests){
            val graph = Graph.fromFile(test)
            val result = graph.isBipartite()
            assert(result)
        }
        tests = mutableListOf<String>()
        for(i in 1..6){
            tests.add("src/resources/4/d4b-$i.txt")
        }
        for(i in 1..6){
            tests.add("src/resources/4/u4b-$i.txt")
        }
        for(test in tests){
            val graph = Graph.fromFile(test)
            val result = graph.isBipartite()
            assert(!result)
        }

    }
}