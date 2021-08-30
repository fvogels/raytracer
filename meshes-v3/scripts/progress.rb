class Progress
  def initialize(total)
    @total = total
    @done = 0
    @last_percentage = 0
    @start_time = Process.clock_gettime(Process::CLOCK_MONOTONIC)
  end

  def step(n = 1)
    @done += n
    report
  end

  def report
    p = percentage_done

    if @last_percentage != p
      @last_percentage = p

      now = Process.clock_gettime(Process::CLOCK_MONOTONIC)
      elapsed_seconds = now - @start_time
      total_estimated = elapsed_seconds / p * 100
      left_estimated = total_estimated * (100 - p) / 100

      STDERR.puts "#{p}% done [passed=#{elapsed_seconds.floor}, total=#{total_estimated.ceil}, left=#{left_estimated.ceil}]"
    end
  end

  def percentage_done
    (@done * 100.0 / @total).floor
  end
end
