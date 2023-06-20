/**
 * An implementation of the Bellman-Ford algorithm. The algorithm finds the shortest path between a
 * starting node and all other nodes in the graph. The algorithm also detects negative cycles.
 *
 * @author William Fiset, william.alexandre.fiset@gmail.com
 */
import java.util.*;
import java.util.stream.Collectors;

class BellmanFordAdjacencyMatrix {

    private int n, start;
    private boolean solved;
    private double[] dist;
    private Integer[] prev;
    private double[][] matrix;

    /**
     * An implementation of the Bellman-Ford algorithm. The algorithm finds the shortest path between
     * a starting node and all other nodes in the graph. The algorithm also detects negative cycles.
     * If a node is part of a negative cycle then the minimum cost for that node is set to
     * Double.NEGATIVE_INFINITY.
     *
     * @param - An adjacency matrix containing directed edges forming the graph
     * @param start - The id of the starting node
     */
    public BellmanFordAdjacencyMatrix(int start, double[][] matrix) {
        this.n = matrix.length;
        this.start = start;
        this.matrix = new double[n][n];

        // Copy input adjacency matrix.
        for (int i = 0; i < n; i++) this.matrix[i] = matrix[i].clone();
    }

    public double[] getShortestPaths() {
        if (!solved) solve();
        return dist;
    }

    public List<Integer> reconstructShortestPath(int end) {
        if (!solved) solve();
        LinkedList<Integer> path = new LinkedList<>();
        if (dist[end] == Double.POSITIVE_INFINITY) return path;
        for (int at = end; prev[at] != null; at = prev[at]) {
            // Return null since there are an infinite number of shortest paths.
            if (prev[at] == -1) return null;
            path.addFirst(at);
        }
        path.addFirst(start);
        return path;
    }

    public List<Integer> solve() {

        // Initialize the distance to all nodes to be infinity
        // except for the start node which is zero.
        dist = new double[n];
        java.util.Arrays.fill(dist, Double.POSITIVE_INFINITY);
        dist[start] = 0;

        // Initialize prev array which will allows for shortest path
        // reconstruction after the algorithm has terminated.
        prev = new Integer[n];

        // For each vertex, apply relaxation for all the edges
        for (int k = 0; k < n - 1; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (dist[i] + matrix[i][j] < dist[j]) {
                        dist[j] = dist[i] + matrix[i][j];
                        prev[j] = i;
                    }

        // Run algorithm a second time to detect which nodes are part
        // of a negative cycle. A negative cycle has occurred if we
        // can find a better path beyond the optimal solution.
        List<Integer> res = new ArrayList<>();
        for (int k = 0; k < n - 1; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (dist[i] + matrix[i][j] < dist[j]) {
                        dist[j] = Double.NEGATIVE_INFINITY;
                        prev[j] = -1;
                        res.add(j);
                    }

        solved = true;

        return res;
    }

    public static <ArraysList> void main(String[] args) {

        Scanner myObj = new Scanner(System.in);

        int n = myObj.nextInt();  // Read user input

        double[][] graph = new double[n][n];

        // Setup completely disconnected graph with the distance
        // from a node to itself to be zero.
        int input;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                input = myObj.nextInt();
                if (Math.abs(input) == 100000) {
                    graph[i][j] = 0;
                    continue;
                }
                graph[i][j] = input;
            }
        }

        int start = 0;
        BellmanFordAdjacencyMatrix solver;
        solver = new BellmanFordAdjacencyMatrix(start, graph);
        double[] d = solver.getShortestPaths();
        List<Integer> res = solver.solve();

        if (res.size() == 0) {
            System.out.println("NO");
        } else {
            System.out.println("YES");
            System.out.println(res.size());
            for (var el : res) {
                System.out.printf("%d ", ++el);
            }
        }
    }
}
