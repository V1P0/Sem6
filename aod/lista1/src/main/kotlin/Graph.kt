import java.io.File
import java.util.*
import kotlin.collections.ArrayDeque
import kotlin.collections.component1
import kotlin.collections.component2


class Graph(val numberOfVertices:Int, val isDirected:Boolean = false) {
    private val adjacencyList = Array(numberOfVertices) { mutableListOf<Int>() }
    fun addEdge(source:Int, destination:Int) {
        adjacencyList[source].add(destination)
        if (!isDirected) {
            adjacencyList[destination].add(source)
        }
    }

    fun addEdges(source:Int, vararg destinations:Int) {
        for (destination in destinations) {
            addEdge(source, destination)
        }
    }
    fun getNeighbours(vertex:Int) = adjacencyList[vertex]

    fun getVertices() = adjacencyList.indices

    fun bfs(startingVertex:Int,visited:BooleanArray = BooleanArray(numberOfVertices),  function:(Int)->Any= ::println, returnParents:Boolean = false) : Optional<List<Int>> {
        val parents = IntArray(numberOfVertices) { -1 }
        val queue = ArrayDeque<Int>()
        queue.add(startingVertex)
        while (queue.isNotEmpty()) {
            val current = queue.removeFirst()
            function(current)
            visited[current] = true
            for (neighbour in getNeighbours(current)) {
                if (!visited[neighbour]) {
                    queue.add(neighbour)
                    parents[neighbour] = current
                    visited[neighbour] = true
                }
            }
        }
        return if (returnParents) Optional.of(parents.toList()) else Optional.empty()
    }

    fun dfs(startingVertex:Int, visited:BooleanArray = BooleanArray(numberOfVertices), function:(input:Int)->Any = ::println, returnParents:Boolean = false) : Optional<List<Int>> {
        val parents = IntArray(numberOfVertices) { -1 }
        val stack = ArrayDeque<Int>()
        stack.add(startingVertex)
        while (stack.isNotEmpty()) {
            val current = stack.removeFirst()
            function(current)
            visited[current] = true
            for (neighbour in getNeighbours(current)) {
                if (!visited[neighbour]) {
                    stack.addFirst(neighbour)
                    parents[neighbour] = current
                    visited[neighbour] = true
                }
            }
        }
        return if (returnParents) Optional.of(parents.toList()) else Optional.empty()
    }

    fun topologicalSort():Optional<List<Int>> {
        if(!isDirected) throw IllegalArgumentException("Graph must be directed")
        var L = mutableListOf<Int>()
        var inDegrees = IntArray(numberOfVertices) { 0 }
        for (i in adjacencyList.indices) {
            for (j in adjacencyList[i]) {
                inDegrees[j]++
            }
        }
        var S = mutableListOf<Int>()
        for (i in inDegrees.indices) {
            if (inDegrees[i] == 0) {
                S.add(i)
            }
        }
        while (S.isNotEmpty()) {
            val n = S.removeAt(0)
            L.add(n)
            for (m in adjacencyList[n]) {
                inDegrees[m]--
                if (inDegrees[m] == 0) {
                    S.add(m)
                }
            }
        }
        for(i in inDegrees) {
            if (i != 0) {
                return Optional.empty()
            }
        }
        return Optional.of(L)
    }

    fun transpose():Graph{
        val graph = Graph(numberOfVertices, isDirected)
        for(i in adjacencyList.indices){
            for(j in adjacencyList[i]){
                graph.addEdge(j, i)
            }
        }
        return graph
    }

    fun fillOrder(v: Int, visited: BooleanArray, outStack: ArrayDeque<Int>) {
        var processed = visited.clone()
        var stack = ArrayDeque<Int>()
        stack.add(v)
        while (stack.isNotEmpty()) {
            val current = stack.first()
            if(!visited[current] && !processed[current]){
                visited[current] = true
                for (neighbour in getNeighbours(current)) {
                    if (!visited[neighbour]) {
                        stack.addFirst(neighbour)
                    }
                }
            }else if(!processed[current]){
                outStack.addFirst(current)
                processed[current] = true
                stack.removeFirst()
            }else{
                stack.removeFirst()
            }
        }
    }


    fun stronglyConnectedComponents():List<List<Int>>{
        var stack: ArrayDeque<Int> = ArrayDeque()
        var visited = BooleanArray(numberOfVertices)
        for(i in adjacencyList.indices){
            if(!visited[i]){
                fillOrder(i, visited, stack)
            }
        }
        var transpose = transpose()
        var components = mutableListOf<List<Int>>()
        visited = BooleanArray(numberOfVertices)
        while(stack.isNotEmpty()){
            val current = stack.removeFirst()
            if(!visited[current]){
                var component = mutableListOf<Int>()
                transpose.dfs(current, visited = visited, function = { component.add(it) })
                components.add(component)
            }
        }
        return components
    }

    fun isBipartite():Boolean{
        var colorArr = IntArray(numberOfVertices) { -1 }
        colorArr[0] = 1
        var q = ArrayDeque<Int>()
        q.add(0)
        while (q.isNotEmpty()) {
            val u = q.removeFirst()
            if (adjacencyList[u].any { colorArr[it] == colorArr[u] }) {
                return false
            }
            for (v in adjacencyList[u]) {
                if (colorArr[v] == -1) {
                    colorArr[v] = 1 - colorArr[u]
                    q.add(v)
                }else if(colorArr[v] == colorArr[u]){
                    return false
                }
            }
        }
        return true
    }

    fun printGraph() {
        for (i in adjacencyList.indices) {
            print("$i -> ")
            for (j in adjacencyList[i]) {
                print("$j ")
            }
            println()
        }
    }

    companion object{
        fun fromFile(fileName:String):Graph{
            val file = File(fileName)
            val lines = file.readLines()
            val directed = lines[0].equals("D")
            val n = lines[1].toInt()
            val m = lines[2].toInt()
            val graph = Graph(n, directed)
            for (i in 3 until m+3) {
                val (source, destination) = lines[i].split(" ").map { it.toInt() }
                graph.addEdge(source-1, destination-1)
            }
            return graph
        }
    }
}

