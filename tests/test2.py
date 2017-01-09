import csv

if __name__ == '__main__':
	with open("out2.csv", 'rb') as f1, open("sample_output2.csv", 'rb') as f2:
  		rdr1 = csv.reader(f1)
  		rdr2 = csv.reader(f2)
		for file1_line in rdr1:
   			file2_line = rdr2.next()
			if file1_line != file2_line:
				print("Find difference in {0}, {1}".format(file1_line, file2_line))
		print("All match!")
