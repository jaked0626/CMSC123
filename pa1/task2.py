from mrjob.job import MRJob
import heapq

# Defining global variable to index visitee name

with open("data.csv", "r") as f:
    first_line = f.readline()
    f.close()

visiteelast_i = first_line.split(",").index("visitee_namelast")

# Map Reduce code

class MRTop10Visitees(MRJob):
    
    def mapper(self, _, line):
        '''
        keys are names of staff, values are counts
        '''
        info = line.split(",")
        if info[visiteelast_i] or info[visiteelast_i + 1]:
            name = ", ".join(info[visiteelast_i:visiteelast_i + 2]).strip(", ")
            yield name, 1

    def combiner(self, name, counts):
        yield name, sum(counts)

    def reducer_init(self):
        '''
        defines heap to track max 10
        '''
        self.max_heap = [(0, "name")] * 10
        heapq.heapify(self.max_heap)

    def reducer(self, name, counts):
        '''
        sums counts of visits per staff, updates max heap
        '''
        num_visits = sum(counts)
        if num_visits >= self.max_heap[0][0]:  # value of min visits in heap
            heapq.heapreplace(self.max_heap, (num_visits, name))
    
    def reducer_final(self):
        for _ in range(10):
            visits, name = heapq.heappop(self.max_heap)
            yield name, visits
        
        


if __name__ == '__main__': MRTop10Visitees.run()
