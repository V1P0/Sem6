class z2 {
    class TestData(val input: String, val expectedOutcome: Boolean)
    @org.junit.jupiter.api.Test
    fun test1(){
        var tests = mutableListOf<TestData>()
        for(i in 1..6){
            tests.add(TestData("src/resources/2/g2a-$i.txt", true))
        }
        for(i in 1..6){
            tests.add(TestData("src/resources/2/g2b-$i.txt", false))
        }
        for(test in tests){
            val graph = Graph.fromFile(test.input)
            val result = graph.topologicalSort()
            assert(result.isPresent == test.expectedOutcome)
        }
    }
}