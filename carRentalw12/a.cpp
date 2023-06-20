// unordered_map<string, bool> visited;
//         priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
//         vector<Edge> mst;

//         for (auto &branch : branches) {
//             string start = branch.first;
//             if (!visited[start]) {
//                 visited[start] = true;
//                 for (auto &edge : graph[start]) {
//                     pq.push(edge);
//                 }

//                 while (!pq.empty()) {
//                     Edge minEdge = pq.top();
//                     pq.pop();
//                     string to = minEdge.to;
//                     if (!visited[to]) {
//                         visited[to] = true;
//                         mst.push_back(minEdge);
//                         for (auto &edge : graph[to]) {
//                             pq.push(edge);
//                         }
//                     }
//                 }
//             }
//         }

//         return mst;