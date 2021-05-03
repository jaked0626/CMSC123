from mrjob.job import MRJob
import re

# Defining global variable to index year

with open("data.csv", "r") as f:
    first_line = f.readline()
    f.close()

year_i = first_line.split(",").index("APPT_START_DATE")

# Map Reduce code

class MRVisitedBothYears(MRJob):
    
    def mapper(self, _, line):
        '''
        yields name as key, year as value
        '''
        info = line.split(",")
        year = re.search(r"2009|2010", info[year_i]) # only pulls 2009 or 2010
        name = ", ".join(info[:2]).strip(", ")
        if year and name:
            yield name, year.group(0)

    def combiner(self, name, year):
        '''
        Takes name and subset of years associated with name and checks 
        for both 2009 and 2010. If both exist in the subset, yields name
        and string "Both" to send to reducer. Otherwise, sends name and the 
        year found in the subset. 
        '''
        years = set(year)
        if len(years) > 1:
            yield name, "Both"
        else:
            year = years.pop()
            yield name, year
    
    def reducer(self, name, year): 
        '''
        iterates through generator for each name, adds years to a set
        and as soon as it is clear the set contains both 2009 and 2010, 
        breaks loop and yields name 
        '''
        years = set()
        for x in year: 
            years.add(x)
            if "Both" in years or len(years) > 1: 
                yield None, name
                break  # does this break function even for generators? 

                ### GRADER COMMENT
                # Good question! The break exits the for loop for the current name generator,
                # but it's essentially redundant for a given name because you yield at most
                # one value for a name

if __name__ == '__main__': MRVisitedBothYears.run()
