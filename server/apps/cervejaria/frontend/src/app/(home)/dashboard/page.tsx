import EventCalendar from "@/app/components/eventCalendar";
import TemperatureChart from "@/app/components/temperatureChart";
import React from "react";

const UserCard = ({ type, id }: { type: string; id: number }) => {
  return (
    <div className="rounded-2xl odd:bg-gray-200 even:bg-gray-400 p-4 flex-1 min-w-[130px]">
      <div className="flex justify-between items-center">
        <span className="text-[10px] bg-white px-2 py-1 rounded-full text-green-600">
          Lote {id}
        </span>
        {/* <Image src="/more.png" alt="" width={20} height={20} /> */}
      </div>
      <h1 className="text-2xl font-semibold my-4">1,234</h1>
      <h2 className="capitalize text-sm font-medium text-gray-500">{type}s</h2>
    </div>
  );
};

const Dashboard = () => {
  return (
    <div className="flex md:flex-row p-4 gap-4">
      {/* LEFT  */}
      <div className="w-full lg:w-3/4 flex flex-col gap-8">
        <div className="flex flex-wrap justify-between gap-4">
          <UserCard type="student" id={1} />
          <UserCard type="teacher" id={2} />
          <UserCard type="parent" id={3} />
          <UserCard type="staff" id={4} />
        </div>
        <div className="w-full h-[400px]">
          <TemperatureChart />
        </div>
      </div>
      <div className="w-full lg:w-1/4 flex flex-col gap-8">
        <EventCalendar />
      </div>
    </div>
  );
};

export default Dashboard;
