require 'benchmark'

totalA = 0
totalB = 0
iterations = 50
iterations.times do
  pairs = []
  pairCount = (500..2000).to_a.sample
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

  Benchmark.bm (1) do |x|
    a = 0
    b = 0
    x.report ("fast way:") { a = %x[./a3 < input.txt] }
    x.report ("naiive way:") { b = %x[./a3naiive < input.txt] }
    raise if a != b
    puts a
    puts b
    totalA = totalA + a.to_f
    totalB = totalB + b.to_f
  end
  puts "============== Total ==============="
  puts "Fast way: #{totalA / iterations}"
  puts "Slow way: #{totalB / iterations}"
end