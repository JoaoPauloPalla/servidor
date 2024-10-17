import {
  CookingPot,
  HouseIcon,
  List,
  LucideIcon,
  Settings,
} from "lucide-react";
import Link from "next/link";
import { usePathname } from "next/navigation";

const menuItems = [
  {
    title: "Dashboard",
    items: [
      {
        label: "Home",
        icon: { HouseIcon },
        href: "/dashboard",
        visible: ["admin", "user"],
      },
      {
        label: "Stock",
        icon: { List },
        href: "/stock",
        visible: ["admin", "user"],
      },
      {
        label: "Recipes",
        icon: { CookingPot },
        href: "/recipes",
        visible: ["admin", "user"],
      },
      {
        label: "Settings",
        icon: { Settings },
        href: "/settings",
        visible: ["admin"],
      },
    ],
  },
  {},
];

interface SidebarLinkProps {
  icon: LucideIcon;
  label: string;
  href: string;
  isCollapsed: boolean;
}

const SidebarLink = ({
  href,
  icon: Icon,
  label,
  isCollapsed,
}: SidebarLinkProps) => {
  const pathname = usePathname();
  const isActive =
    pathname === href || (pathname === "/" && href === "/dashboard");

  return (
    <Link href={href}>
      <div
        className={`cursor-pointer flex items-center ${
          isCollapsed ? "justify-center py-4" : "justify-start px-8 py-4"
        }
        hover:text-blue-500 hover:bg-blue-100 gap-3 transition-colors ${
          isActive ? "bg-blue-200 text-white" : ""
        }
      }`}
      >
        <Icon className="w-6 h-6 !text-gray-700" />

        <span
          className={`${
            isCollapsed ? "hidden" : "block"
          } font-medium text-gray-700`}
        >
          {label}
        </span>
      </div>
    </Link>
  );
};

export default SidebarLink;
