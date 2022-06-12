// https://leetcode.com/problems/largest-component-size-by-common-factor/

// You are given an integer array of unique positive integers nums. Consider the following graph:

// There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
// There is an undirected edge between nums[i] and nums[j] if nums[i] and nums[j] share a common factor greater than 1.
// Return the size of the largest connected component in the graph.

// Example:
// Input: nums = [4,6,15,35]
// Output: 4

// -- Solution from website using union-find over the prime factors:

// - Algorithm in two general steps:

// Step 1). Decompose each number into its prime factors and apply Union() operations on the series of prime factors.

// We iterate through each number, denoted as num. For each number, we decompose it into prime factors.

// We join all groups that possess these prime factors, by applying Union() operation on each adjacent pair of prime factors.

// In addition, we use a hash table to keep the mapping between each number and its any of prime factors. Later, we would use this table 
// to find out which group that each number belongs to.

// Step 2). Iterate through each number a second time, to find out the final group that the number belongs to.

// Since we build Union-Find sets solely on the prime factors, we could find out which group that each prime factor belongs
// to, i.e. prime_factor -> group_id.

// Thanks to the mapping between the number and its prime factor, i.e. {num -> prime_factor}, we could now find out which group that
// each number belongs with the above Union-Find sets, i.e. num -> prime_factor -> group_id.

class Solution {

    public int largestComponentSize(int[] A) {
        int maxValue = Arrays.stream(A).reduce(A[0], (x, y) -> x > y ? x : y);
        DisjointSetUnion dsu = new DisjointSetUnion(maxValue);

        HashMap<Integer, Integer> numFactorMap = new HashMap<>();

        // Union-Find on the prime factors.
        for (int num : A) {
            // find all the unique prime factors.
            List<Integer> primeFactors = new ArrayList<>(
      new HashSet<>(this.primeDecompose(num)));

            // map a number to its first prime factor
            numFactorMap.put(num, primeFactors.get(0));
            // Merge all the groups that contain the prime factors.
            for(int i=0; i<primeFactors.size()-1; ++i)
                dsu.union(primeFactors.get(i), primeFactors.get(i+1));
        }

        // count the size of group one by one
        int maxGroupSize = 0;
        HashMap<Integer, Integer> groupCount = new HashMap<>();
        for (int num : A) {
            Integer groupId = dsu.find(numFactorMap.get(num));
            Integer count = groupCount.getOrDefault(groupId, 0);
            groupCount.put(groupId, count+1);
            maxGroupSize = Math.max(maxGroupSize, count+1);
        }

        return maxGroupSize;
    }

    protected List<Integer> primeDecompose(int num) {
        List<Integer> primeFactors = new ArrayList<Integer>();
        int factor = 2;
        while (num >= factor * factor) {
            if (num % factor == 0) {
                primeFactors.add(factor);
                num = num / factor;
            } else {
                factor += 1;
            }
        }
        primeFactors.add(num);
        return primeFactors;
    }

}


class DisjointSetUnion {
    private int[] parent;
    private int[] size;

    public DisjointSetUnion(int size) {
        this.parent = new int[size + 1];
        this.size = new int[size + 1];
        for (int i = 0; i < size + 1; ++i) {
            this.parent[i] = i;
            this.size[i] = 1;
        }
    }

    /** return the component id that the element x belongs to. */
    public int find(int x) {
        if (this.parent[x] != x)
            this.parent[x] = this.find(this.parent[x]);
        return this.parent[x];
    }

    /**
     * merge the two components that x, y belongs to respectively, 
     * and return the merged component id as the result.
     */
    public int union(int x, int y) {
        int px = this.find(x);
        int py = this.find(y);

        // the two nodes share the same group
        if (px == py)
            return px;

        // otherwise, connect the two sets (components)
        if (this.size[px] > this.size[py]) {
            // add the node to the union with less members.
            // keeping px as the index of the smaller component
            int temp = px;
            px = py;
            py = temp;
        }

        // add the smaller component to the larger one
        this.parent[px] = py;
        this.size[py] += this.size[px];
        return py;
    }
}


// My wip solution below:

/*
unordered_set<int> GetPrimeFactors(int num) {
	unordered_set<int> factors;
	for (int f = 2; f * f <= num; ++f) {
		if (num % f == 0) {
			factors.insert(f);
			while (num % f == 0) {
				num /= f;
			}
		}
	}

	if(num > 1) factors.insert(num);
	return factors;
}

bool AreConnected(const unordered_set<int>& a, const unordered_set<int>& b) {
	for (int el : a) {
		if (b.find(el) != b.end()) {
			return true;
		}
	}

	return false;
}

int Find(unordered_map<int, int>& parent, int num) {
	if (parent[num] != num) {
		parent[num] = Find(parent, parent[num]);
	}

	return parent[num];
}

void Union(unordered_map<int, int>& parent, int a, int b) {
	parent[Find(parent, a)] = Find(parent, b);
}

int largestComponentSize(vector<int>& nums) {
	unordered_map<int, unordered_set<int>> prime_factors;
	unordered_map<int, int> parent;
	for (int num : nums) {
		unordered_set<int> prime_factors = GetPrimeFactors(num);
		parent[num] = num;
	}

	// for (int i = 0; i < nums.size(); ++i) {
	// 	for (int j = i + 1; j < nums.size(); ++j) {
	// 		if (AreConnected(prime_factors[nums[i]], prime_factors[nums[j]])) {
	// 			Union(parent, nums[i], nums[j]);
	// 		}
	// 	}
	// }

	

	unordered_map<int, int> groups;
	for (int num : nums) {
		int group = Find(parent, num);
		if (groups.find(group) == groups.end()) {
			groups[group] = 1;
		} else {
			++groups[group];
		}
	}

	int max_count = 0;
	for (pair<int, int> group_count : groups) {
		if (group_count.second > max_count) {
			max_count = group_count.second;
		}
	}

	return max_count;
}

int main() {
	// Test GetPrimeFactors:
	// unordered_set<int> factors = GetPrimeFactors(90);
	// for (int f : factors) {
	// 	cout << f << endl;
	// }
	
	// vector<int> nums = {4,6,15,35};
	vector<int> nums = {2,3,6,7,4,12,21,39};
	cout << largestComponentSize(nums);

	return 0;
}
*/