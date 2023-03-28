class z3 {
    @org.junit.jupiter.api.Test
    fun test1(){
        var tests = mutableListOf<String>()
        for(i in 1..6){
            tests.add("src/resources/3/g3-$i.txt")
        }
        for(test in tests){
            val graph = Graph.fromFile(test)
            val result = graph.stronglyConnectedComponents()
            assert(result.size==5)
        }
    }
}