class z1 {

    fun graf1():Graph{
        val graph = Graph(6, true)
        graph.addEdges(0,1,2)
        graph.addEdges(1,2,3,4)
        graph.addEdges(2,4,5)
        graph.addEdges(3,4)
        graph.addEdges(4,5)
        return graph
    }

    fun graf2():Graph{
        val graph = Graph(8, true)
        graph.addEdges(0,1,3)
        graph.addEdges(1,2,5)
        graph.addEdges(2,3)
        graph.addEdges(3,7)
        graph.addEdges(4,7)
        graph.addEdges(5,4,6)
        graph.addEdges(6,2)
        graph.addEdges(7,6)
        return graph
    }

    fun graf3():Graph{
        val graph = Graph(9, true)
        graph.addEdges(0,1,2,4)
        graph.addEdges(1,3,4)
        graph.addEdges(2,4,5)
        graph.addEdges(3,7,4)
        graph.addEdges(4,5)
        graph.addEdges(5,6,8)
        graph.addEdges(6,3,7)
        graph.addEdges(7)
        graph.addEdges(8,6,7)
        return graph
    }

    @org.junit.jupiter.api.Test
    fun test1dfs() {
        val myGraph = graf1()
        myGraph.printGraph()
        myGraph.dfs(0, returnParents = true).get().forEachIndexed() { index, value -> println("$value -> $index") }
    }

    @org.junit.jupiter.api.Test
    fun test2dfs() {
        val myGraph = graf2()
        myGraph.printGraph()
        myGraph.dfs(0, returnParents = true).get().forEachIndexed() { index, value -> println("$value -> $index") }
    }

    @org.junit.jupiter.api.Test
    fun test3dfs() {
        val myGraph = graf3()
        myGraph.printGraph()
        myGraph.dfs(0, returnParents = true).get().forEachIndexed { index, value -> println("$value -> $index") }
    }

    @org.junit.jupiter.api.Test
    fun test1bfs() {
        val myGraph = graf1()
        myGraph.printGraph()
        myGraph.bfs(0, returnParents = true).get().forEachIndexed() { index, value -> println("$value -> $index") }
    }

    @org.junit.jupiter.api.Test
    fun test2bfs() {
        val myGraph = graf2()
        myGraph.printGraph()
        myGraph.bfs(0, returnParents = true).get().forEachIndexed() { index, value -> println("$value -> $index") }
    }

    @org.junit.jupiter.api.Test
    fun test3bfs() {
        val myGraph = graf3()
        myGraph.printGraph()
        myGraph.bfs(0, returnParents = true).get().forEachIndexed { index, value -> println("$value -> $index") }
    }


}