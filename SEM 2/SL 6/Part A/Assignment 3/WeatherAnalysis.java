import java.io.IOException;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Mapper.Context;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class WeatherAnalysis {

	public static class MaxTemperatureMapper  
	extends Mapper<LongWritable, Text, Text, IntWritable> {
		private static final int MISSING = 9999;
		
		
		public void map(LongWritable key, Text value, Context context)      
				throws IOException, InterruptedException {    
			String line = value.toString();    
			String year = line.substring(15, 19);    
			int airTemperature;    
			if (line.charAt(87) == '+') { 
				// parseInt doesn't like leading plus signs      
				airTemperature = Integer.parseInt(line.substring(88, 92));    } 
			else {
				airTemperature = Integer.parseInt(line.substring(87, 92));    }   
			String quality = line.substring(92, 93);    
			if (airTemperature != MISSING && quality.matches("[01459]")) {      
				context.write(new Text(year), new IntWritable(airTemperature));    
				}  
			}
		}
	
	public static class MaxTemperatureReducer 
	extends Reducer<Text, IntWritable, Text, IntWritable> {  
		
		int maxValue = Integer.MIN_VALUE; 
		int minValue = Integer.MAX_VALUE;
		Text minYear = new Text(), maxYear = new Text();
		  
		public void reduce(Text key, Iterable<IntWritable> values,      Context context)      
				throws IOException, InterruptedException {    
			
			int sum = 0, count = 0;
			for (IntWritable value : values) {      
				//maxValue = Math.max(maxValue, value.get()); 
				//minValue = Math.min(minValue, value.get()); 
				sum += value.get();
				count ++;
				} 
			sum /= count;
			if(sum < minValue) {
				minValue = sum;
				minYear.set(key);
			}
			else if (sum > maxValue) {
				maxValue = sum;
				maxYear.set(key);
			}
			//context.write(key, new IntWritable(maxValue));
			//context.write(key, new IntWritable(minValue));  
			}
		
		
		public void cleanup(Context context) throws IOException, InterruptedException {
			context.write(maxYear, new IntWritable(maxValue));
			context.write(minYear, new IntWritable(minValue)); 
		}
		}
	 
	 public static void main(String[] args) throws Exception {    
		 if (args.length != 2) {     
			 System.err.println("Usage: MaxTemperature <input path> <output path>");      
			 System.exit(-1);    
			 
		}
		 Job job = new Job();    
		 job.setJarByClass(WeatherAnalysis.class);   
		 job.setJobName("Max temperature");    
		 FileInputFormat.addInputPath(job, new Path(args[0]));    
		 FileOutputFormat.setOutputPath(job, new Path(args[1]));
		 job.setMapperClass(MaxTemperatureMapper.class);    
		 job.setReducerClass(MaxTemperatureReducer.class);   
		 job.setOutputKeyClass(Text.class);    
		 job.setOutputValueClass(IntWritable.class);    
		 System.exit(job.waitForCompletion(true) ? 0 : 1);
	 }
}
			
	
