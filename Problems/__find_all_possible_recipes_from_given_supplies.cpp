#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies (Google problem)
// Remember: cycle here also invalidates the recipe, so used "rec_stack" to check for cycle in 
// directed graph and used "can_make" as "visited" below.
// A partial topo ordering also works here (even simpler/more intuitive).

// You have information about n different recipes. You are given a string array recipes and a 2D string array 
// ingredients. The ith recipe has the name recipes[i], and you can create it if you have all the needed ingredients 
// from ingredients[i]. A recipe can also be an ingredient for other recipes, i.e., ingredients[i] may 
// contain a string that is in recipes.

// You are also given a string array supplies containing all the ingredients that you initially have, and you 
// have an infinite supply of all of them.
// Return a list of all the recipes that you can create. You may return the answer in any order.
// Note that two recipes may contain each other in their ingredients.

// Example 1:
// Input: recipes = ["bread"], ingredients = [["yeast","flour"]], supplies = ["yeast","flour","corn"]
// Output: ["bread"]
// Explanation:
// We can create "bread" since we have the ingredients "yeast" and "flour".

// Example 2:
// Input: recipes = ["bread","sandwich"], ingredients = [["yeast","flour"],["bread","meat"]], supplies = ["yeast","flour","meat"]
// Output: ["bread","sandwich"]
// Explanation:
// We can create "bread" since we have the ingredients "yeast" and "flour".
// We can create "sandwich" since we have the ingredient "meat" and can create the ingredient "bread".

// Example 3: (gives error if not using separate rec_stack)
// Input: recipes = ["bread","sandwich","burger"], ingredients = [["yeast","flour"],["bread","meat"],["sandwich","meat","bread"]], supplies = ["yeast","flour","meat"]
// Output: ["bread","sandwich","burger"]
// Explanation:
// We can create "bread" since we have the ingredients "yeast" and "flour".
// We can create "sandwich" since we have the ingredient "meat" and can create the ingredient "bread".
// We can create "burger" since we have the ingredient "meat" and can create the ingredients "bread" and "sandwich".

// If you run Kahn's Algorithm (for Topo Ordering) on a graph with a cycle, the output is:
// 1) It is a valid topological ordering of the acyclic part of the graph.
// 2) It includes all nodes reachable before getting stuck on a cycle.
// 3) The nodes missing from the output are precisely those that belong to *(or depend on)* cycles.

// Edge u -> v if u is a needed ingredient for v (trick for the topo ordering to be right here). Using Topo Ordering elegantly here.
// Could even improve space complexity below if using a map recipe_to_idx and then using an int as key in the graph g and only a vector<int> 
// for indegrees, would also be better in time (by a constant) without needing to hash the strings each time during graph traversals.
//     How many unique recipes (nodes) do you expect? (If N is large, the O(N·L) mapping cost may be offset by O(E·L) savings in traversal - this is the tradeoff).
// O(n + m + s) in time and space, where n is #recipes, m is the total number of ingredients across all recipes and s is the #supplies.
vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
    vector<string> created_recipes;
    unordered_set<string> supplies_set(supplies.begin(), supplies.end());
    unordered_map<string, int> indegree;
    unordered_map<string, vector<string>> g;  // dependency graph.
    for (const string& recipe : recipes) {
        g[recipe] = {};
        indegree[recipe] = 0;
    }
    for (int i = 0; i < ingredients.size(); ++i) {
        for (int j = 0; j < ingredients[i].size(); ++j) {
            if (!supplies_set.count(ingredients[i][j])) {  // only if the ingredient is not already available in the initial supplies - this ensures that the in-degree of a recipe reflects only the number of unavailable ingredients it depends on.
                g[ingredients[i][j]].push_back(recipes[i]);  // the ingredients that do not appear neither in recipes nor in supplies will start will in-degree 0 but will not initially enter q below (we iterate through recipes to initialize q) and then will never enter q (as they will not be reachable from a neighbor since they do not depend on anyone) - one of the test cases.
                ++indegree[recipes[i]];
            }
        }
    }

    // Start with recipes that only need supplies (in-degree zero, already available to be made).
    queue<string> q;
    for (const string& recipe : recipes) {
        if (indegree[recipe] == 0) {
            q.push(recipe);
        }
    }

    while(!q.empty()) {
        string item = q.front();
        q.pop();
        created_recipes.push_back(item);  // the partial topo ordering (elements in the acyclic part of the graph and that do not depend on any cycle).

        for (const string& neigh : g[item]) {
            if (--indegree[neigh] == 0) {
                q.push(neigh);
            }
        }
    }

    return created_recipes;
}

// Improved version of the above using integer indices for recipes to avoid repeated hashing on recipe strings.
vector<string> findAllRecipesAIImprovedIndexMapping(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
	vector<string> created_recipes;
	unordered_set<string> supplies_set(supplies.begin(), supplies.end());

	int n = recipes.size();
	unordered_map<string, int> recipe_to_idx;
    for (int i = 0; i < n; ++i) {
        recipe_to_idx[recipes[i]] = i;
    }

    // indegree only for recipes (index-based). Adjacency maps an ingredient name -> list of recipe indices that depend on it.
	vector<int> indegree(n, 0);
	unordered_map<string, vector<int>> g;  // ingredient -> list of recipe indices

	for (int i = 0; i < ingredients.size(); ++i) {
		for (const string& ing : ingredients[i]) {
			if (!supplies_set.count(ing)) {
				g[ing].push_back(i);
				++indegree[i];  // recipe i needs one more ingredient that is not initially available.
			}
		}
	}

	// Start with recipes that only need supplies (in-degree zero)
	queue<int> q;
	for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

	while (!q.empty()) {
		int idx = q.front();
		q.pop();
		created_recipes.push_back(recipes[idx]);

		// When a recipe becomes available it can act as an ingredient for others.
		const string& item = recipes[idx];
		auto it = g.find(item);
        if (it == g.end()) {
            continue;
        }
        for (int neigh_idx : it->second) {
            if (--indegree[neigh_idx] == 0) {
                q.push(neigh_idx);
            }
        }
	}

	return created_recipes;
}

// My other solution below using "rec_stack" to check for cycle in directed graph and using "can_make" as "visited".
// "can_make" here also makes the job of "visited".
bool canCreateDfs(const string& recipe,
                  const unordered_map<string, vector<string>>& g,
                  unordered_set<string>& rec_stack,
                  unordered_map<string, bool>& can_make) {
    if (can_make.count(recipe)) {
        return can_make.at(recipe);
    }
    if (!g.count(recipe) || g.at(recipe).empty()) {
        can_make[recipe] = false;
        return false;
    }
    rec_stack.insert(recipe);

    for (const string& neighbor : g.at(recipe)) {
        if (rec_stack.count(neighbor) || !canCreateDfs(neighbor, g, rec_stack, can_make)) {  // if we have a cycle we should also return false.
            can_make[recipe] = false;
            return false;
        }
    }

    can_make[recipe] = true;
    rec_stack.erase(recipe);
    return true;
}

vector<string> findAllRecipesWithDfsAndRecStack(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
    unordered_map<string, vector<string>> g;
    for (int i = 0; i < recipes.size(); ++i) {
        g[recipes[i]] = ingredients[i];
    }
    unordered_map<string, bool> can_make;
    for (const string& supply : supplies) {
        can_make[supply] = true;
    }

    vector<string> ans;
    unordered_set<string> rec_stack;
    for (const string& recipe : recipes) {
        rec_stack.clear();
        if (canCreateDfs(recipe, g, rec_stack, can_make)) {
            ans.push_back(recipe);
        }
    }

    return ans;
}

// My other solution below (more complex and also doing unnecessary job of also adding supplies to the graph).
// Edge u -> v if u is a needed ingredient for v.
vector<string> findAllRecipesOtherWithTopoOrdering(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
	vector<string> topo_ordering;
	unordered_set<string> supplies_set(supplies.begin(), supplies.end());
	unordered_map<string, int> indegree;
	unordered_map<string, vector<string>> g;
	for (const string& supply : supplies) {
		g[supply] = {};
		indegree[supply] = 0;
	}
	for (const string& recipe : recipes) {
		g[recipe] = {};
		indegree[recipe] = 0;
	}
	for (int i = 0; i < ingredients.size(); ++i) {
		for (int j = 0; j < ingredients[i].size(); ++j) {
			if (!g.count(ingredients[i][j])) {
				indegree[ingredients[i][j]] = -1;  // an ingredient that is not a supply nor a recipe will never be able to be made (never enter the queue).
			}
			g[ingredients[i][j]].push_back(recipes[i]);
			++indegree[recipes[i]];
		}
	}

	queue<string> q;
	for (const auto& [item, _] : g) {
		if (indegree[item] == 0) {
			q.push(item);
		}
	}

	while(!q.empty()) {
		string item = q.front();
		q.pop();
		if (!supplies_set.count(item)) {
			topo_ordering.push_back(item);
		}

		for (const string& neigh : g[item]) {
			if (--indegree[neigh] == 0) {
				q.push(neigh);
			}
		}
	}

	return topo_ordering;
}

static void printVec(const vector<string>& v) {
	cout << "[";
	for (int i = 0; i < v.size(); ++i) {
		cout << '"' << v[i] << '"';
        if (i + 1 < v.size()) {
            cout << ", ";
        }
    }
	cout << "]" << endl;
}

int main() {
	// Example 1
	vector<string> recipes1 = {"bread"};
	vector<vector<string>> ingredients1 = {{"yeast","flour"}};
	vector<string> supplies1 = {"yeast","flour","corn"};
	vector<string> out1 = findAllRecipes(recipes1, ingredients1, supplies1);
	cout << "Example 1 output: "; printVec(out1);

	// Example 2
	vector<string> recipes2 = {"bread","sandwich"};
	vector<vector<string>> ingredients2 = {{"yeast","flour"},{"bread","meat"}};
	vector<string> supplies2 = {"yeast","flour","meat"};
	vector<string> out2 = findAllRecipes(recipes2, ingredients2, supplies2);
	cout << "Example 2 output: "; printVec(out2);

	// Example 3
	vector<string> recipes3 = {"bread","sandwich","burger"};
	vector<vector<string>> ingredients3 = {{"yeast","flour"},{"bread","meat"},{"sandwich","meat","bread"}};
	vector<string> supplies3 = {"yeast","flour","meat"};
	vector<string> out3 = findAllRecipes(recipes3, ingredients3, supplies3);
	cout << "Example 3 output: "; printVec(out3);

	return 0;
}