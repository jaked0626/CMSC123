from mrjob.job import MRJob


# Defining global variable to index visitee name

with open("data.csv", "r") as f:
    first_line = f.readline()
    f.close()

visiteelast_i = first_line.split(",").index("visitee_namelast")

# Map Reduce code

class MRGuestAndStaff(MRJob):
    
    def mapper(self, _, line):
        '''
        staff and guest names as key, "S" and "G" as indicators of 
        status for values
        '''
        info = line.split(",")

        if info[visiteelast_i] and info[visiteelast_i + 1]:  # not empty
            staff_name = ", ".join(info[visiteelast_i:visiteelast_i + 2]).strip()
            yield staff_name, "S"

        if info[0] and info[1]:  # not empty
            guest_name = ", ".join(info[:2]).strip()
            yield guest_name, "G"
    
    def combiner(self, name, status):
        '''
        Takes name and subset of statuses associated with name and checks 
        for both "G" and "S". If both exist in the subset, yields name
        and string "Both" to send to reducer. Otherwise, sends name and the 
        status found in the subset. 
        '''
        guest_staff = set(status)
        if len(guest_staff) >1:
            yield name, "Both"
        else:
            stat = guest_staff.pop()
            yield name, stat

    def reducer(self, name, status): 
        '''
        goes through generator, inspects each status value, and 
        breaks loop as soon as it is clear person has both
        '''
        guest_or_staff = set()
        for x in status: 
            guest_or_staff.add(x)
            if "Both" in guest_or_staff or len(guest_or_staff) > 1: 
                yield None, name
                break

    """ def reducer(self, name, status):
        guest_staff = set(status)
        if len(guest_staff) > 1:
            yield None, name """  # initial approach but not as efficient? 


if __name__ == '__main__': MRGuestAndStaff.run()



    


