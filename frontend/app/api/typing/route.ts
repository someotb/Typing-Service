import axios from "axios";
import { NextRequest } from "next/server";

export async function GET(request: NextRequest) {
  try {
    const cppResponse = await axios.get("http://localhost:8081/typing");
    const data = cppResponse.data;

    return new Response(JSON.stringify(data), {
      status: 200,
      headers: { "Content-Type": "application/json" },
    });
  } catch (error) {
    return new Response(
      JSON.stringify({ error: "Failed to fetch text from C++ server" }),
      { status: 500, headers: { "Content-Type": "application/json" } },
    );
  }
}
