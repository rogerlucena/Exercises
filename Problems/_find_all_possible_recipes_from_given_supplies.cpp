#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies (Google problem)
// Remember: cycle here also invalidates the recipe, so used "rec_stack" to check for cycle in 
// directed graph and used "can_make" as "visited" below.
// Topo ordering could also have worked here (maybe even simpler, todo: implement later).

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

// My solution below using "rec_stack" to check for cycle in directed graph and using "can_make" as "visited".
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

vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
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

int main() {
	cout << "Hello, World!";
	return 0;
}