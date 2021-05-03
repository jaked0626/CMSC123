from mrjob.job import MRJob

class MRVisitorsCount(MRJob):
    
    def mapper(self, _, line):
        '''
        keys are names, values are counts
        '''
        info = line.split(",")
        if info[0] or info[1]:  # First name or last name is written down
            name = ", ".join(info[:2]).strip(", ")  # remove commas and spaces
            yield name, 1

    def combiner(self, name, counts):
        yield name, sum(counts)

    def reducer(self, name, counts):
        '''
        sum counts for each key and return those 
        greater than 10
        '''
        num_visits = sum(counts)
        if num_visits >= 10:
            yield name, num_visits




### GRADER COMMENT
# Please put the run command on a new line, as one-line block statements
# are generally considered poor style
if __name__ == '__main__': MRVisitorsCount.run()