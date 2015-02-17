require 'benchmark'

totalA = 0
totalB = 0
iterations = 50
iterations.times do
  pairs = []
  pairCount = 4000
  xs = ys = (pairCount*2..pairCount*4).to_a
  pairCount.times do
    x = xs.shuffle!.pop
    y = ys.shuffle!.pop
    pairs.push([x,y])
  end

  file = File.open("input.txt", "w")
  file.write("#{pairCount} ")
  pairs.sort_by(&:first).each do |p|
    file.write "#{p.first} #{p.last} #{[0,1].sample} "
  end
  file.close

  c = d = 0
  a = Benchmark.realtime { c = %x[./a3 < input.txt] }
  b = Benchmark.realtime { d = %x[./a3naiive < input.txt] }
  puts "============== Iteration ==============="
  puts "Fast way: #{a}"
  puts "Slow way: #{b}"

  totalA += a
  totalB += b

  raise if c != d
end
puts "============== Total ==============="
puts "Fast way: #{totalA / iterations}"
puts "Slow way: #{totalB / iterations}"
