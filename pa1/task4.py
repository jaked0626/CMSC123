from mrjob.job import MRJob

with open("data.csv", "r") as f:
    first_line = f.readline()
    f.close()

visiteelast_i = first_line.split(",").index("visitee_namelast")

class MRGuestAndStaff(MRJob):
    
    def mapper(self, _, line):
        info = line.split(",")

        if info[visiteelast_i] and info[visiteelast_i + 1]:  # not empty
            staff_name = ", ".join(info[visiteelast_i:visiteelast_i + 2]).strip()
            yield staff_name, "S"

        if info[0] and info[1]:  # not empty
            guest_name = ", ".join(info[:2]).strip()
            yield guest_name, "G"
    
    # should there be a combiner? 

    def reducer(self, name, status): 
        guest_or_staff = set()
        for x in status: 
            guest_or_staff.add(x)
            if len(guest_or_staff) > 1: 
                yield None, name
                break

    """ def reducer(self, name, status):
        guest_staff = set(status)
        if len(guest_staff) > 1:
            yield None, name """  # initial approach but not as efficient? 


if __name__ == '__main__': MRGuestAndStaff.run()



    


